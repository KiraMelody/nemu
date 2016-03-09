#include "common.h"
#include <stdlib.h>
#include "burst.h"
#define BLOCK_SIZE 64
#define STORAGE_SIZE_L1 64*1024
#define STORAGE_SIZE_L2 4*1024*1024
uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
void ddr3_read(hwaddr_t, void *);
void ddr3_write(hwaddr_t, void *, uint8_t *);
/*
cache block存储空间的大小为64B
cache存储空间的大小为64KB
8-way set associative
标志位只需要valid bit即可
替换算法采用随机方式
write through
not write allocate*/
/* Memory accessing interfaces */
/*
cache block存储空间的大小为64B
cache存储空间的大小为4MB
16-way set associative
标志位包括valid bit和dirty bit
替换算法采用随机方式
write back
write allocate
*/
struct Cache
{
	bool valid;
	int tag;
	uint8_t data[BLOCK_SIZE];
}cache[STORAGE_SIZE_L1/BLOCK_SIZE];
struct SecondaryCache
{
	bool valid,dirty;
	int tag;
	uint8_t data[BLOCK_SIZE];
}cache2[STORAGE_SIZE_L2/BLOCK_SIZE];
void init_cache()
{
	int i;
	for (i = 0;i < 1024;i ++)
	{
		cache[i].valid = false;
		cache[i].tag = 0;
		memset (cache[i].data,0,BLOCK_SIZE);
	}
	for (i = 0;i < 65536;i ++)
	{
		cache2[i].valid = false;
		cache2[i].dirty = false;
		cache2[i].tag = 0;
		memset (cache2[i].data,0,BLOCK_SIZE);
	}
}
uint32_t secondarycache_read(hwaddr_t addr) 
{
	uint32_t g = (addr >> 6) & ((1<<12) - 1); //group number
	uint32_t block = (addr >> 6)<<6;
	int i;
	bool v = false;
	for (i = g * 16 ; i < (g + 1) * 16 ;i ++)
	{
		if (cache2[i].tag == (addr >> 18)&& cache2[i].valid)
			{
				v = true;
				break;
			}
	}
	if (!v)
	{
		int j;
		for (i = g * 16 ; i < (g + 1) * 16 ;i ++)
		{
			if (!cache2[i].valid)break;
		}
		if (i == (g + 1) * 16)//ramdom
		{
			srand (0);
			i = g * 16 + rand() % 16;
			if (cache2[i].dirty)
			{
				uint8_t mask[BURST_LEN];
				memset(mask, 1, BURST_LEN);
				for (j = 0;j < BLOCK_SIZE/BURST_LEN;j ++);
				//ddr3_write(block + j * BURST_LEN, cache2[i].data + j * BURST_LEN,mask);
			}
		}
		cache2[i].valid = true;
		cache2[i].tag = addr >> 18;
		cache2[i].dirty = false;
		for (j = 0;j < BURST_LEN;j ++)
		ddr3_read(block + j * BURST_LEN , cache2[i].data + j * BURST_LEN);
	}
	return i;
}
uint32_t cache_read(hwaddr_t addr) 
{
	uint32_t g = (addr>>6) & 0x7f; //group number
	//uint32_t block = (addr >> 6)<<6;
	int i;
	bool v = false;
	for (i = g * 8 ; i < (g + 1) * 8 ;i ++)
	{
		if (cache[i].tag == (addr >> 13)&& cache[i].valid)
			{
				v = true;
				break;
			}
	}
	if (!v)
	{
		int j = secondarycache_read (addr);
		for (i = g * 8 ; i < (g+1)*8 ;i ++)
		{
			if (!cache[i].valid)break;
		}
		if (i == (g + 1) * 8)//ramdom
		{
			srand (0);
			i = g * 8 + rand() % 8;
		}
		cache[i].valid = true;
		cache[i].tag = addr >> 13;
		memcpy (cache[i].data,cache2[j].data,BLOCK_SIZE);
	}
	return i;
}
void secondarycache_write(hwaddr_t addr, size_t len,uint32_t data) {
	uint32_t g = (addr >> 6) & ((1<<12) - 1);  //group number
	uint32_t offset = addr & (BLOCK_SIZE - 1); // inside addr
	int i;
	bool v = false;
	for (i = g * 16 ; i < (g + 1) * 16 ;i ++)
	{
		if (cache2[i].tag == (addr >> 13)&& cache2[i].valid)
			{
				v = true;
				break;
			}
	}
	if (!v)i = secondarycache_read (addr);
	cache2[i].dirty = true;
	memcpy (cache2[i].data + offset , &data , len);
}
void cache_write(hwaddr_t addr, size_t len,uint32_t data) {
	uint32_t g = (addr>>6) & 0x7f; //group number
	uint32_t offset = addr & (BLOCK_SIZE - 1); // inside addr
	int i;
	bool v = false;
	for (i = g * 8 ; i < (g + 1) * 8 ;i ++)
	{
		if (cache[i].tag == (addr >> 13)&& cache[i].valid)
			{
				v = true;
				break;
			}
	}
	if (v)
	{
		memcpy (cache[i].data + offset , &data , len);
	}
	secondarycache_write(addr,len,data);
}
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	uint32_t offset = addr & (BLOCK_SIZE - 1); // inside addr
	uint32_t block = cache_read(addr);
	uint8_t temp[4];
	memset (temp,0,sizeof (temp));
	if (offset + len >= BLOCK_SIZE) 
	{
		uint32_t _block = cache_read(addr + len);
		memcpy(temp,cache[block].data + offset, BLOCK_SIZE - offset);
		memcpy(temp + BLOCK_SIZE - offset,cache[_block].data, len - (BLOCK_SIZE - offset));
	}
	else
	{
		memcpy(temp,cache[block].data + offset,len);
	}
	int zero = 0;
	uint32_t tmp = unalign_rw(temp + zero, 4) & (~0u >> ((4 - len) << 3)); 
	uint32_t ground = dram_read(addr, len) & (~0u >> ((4 - len) << 3));
	Assert (tmp == ground,"cache = 0x%x , dram = 0x%x , len = %d\n",tmp,ground,(int)len);
	return tmp;
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	cache_write(addr, len, data);
	//dram_write(addr, len, data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_write(addr, len, data);
}

