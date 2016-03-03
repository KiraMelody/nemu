#include "common.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
/*
cache block存储空间的大小为64B
cache存储空间的大小为64KB
8-way set associative
标志位只需要valid bit即可
替换算法采用随机方式
write through
not write allocate*/
/* Memory accessing interfaces */
struct Cache
{
	bool valid;
	int tag;
	int group;
	uint8_t data[64];
}cache[1024];


/*uint32_t cache_read(hwaddr_t addr, size_t len) {
	uint32_t g = (addr>>6) & 0x7f; //group number
	uint32_t offset = addr & 0x3f; // inside addr
	uint8_t temp[50];
	int i;
	bool v = false;
	for (i = g * 8 ; i < (g+1)*8 ;i ++)
	{
		if (cache[i].tag == (addr >> 13)&& valid)
			{
				v = true;
				memcpy (cache + offset,temp,BURST_LEN);
			}
	}
	if (!v)return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
	if (offset + len > BURST_LEN) {
		memcpy(cache + offset + BURST_LEN, temp + BURST_LEN,BURST_LEN);
	}
	return unalign_rw(temp + offset, 4);
}*/
// static void ddr3_write(hwaddr_t addr, void *data, uint8_t *mask) {
// 	Assert(addr < HW_MEM_SIZE, "physical address %x is outside of the physical memory!", addr);

// 	dram_addr temp;
// 	temp.addr = addr & ~BURST_MASK;
// 	uint32_t rank = temp.rank;
// 	uint32_t bank = temp.bank;
// 	uint32_t row = temp.row;
// 	uint32_t col = temp.col;

// 	if(!(rowbufs[rank][bank].valid && rowbufs[rank][bank].row_idx == row) ) {
// 		/* read a row into row buffer */
// 		memcpy(rowbufs[rank][bank].buf, dram[rank][bank][row], NR_COL);
// 		rowbufs[rank][bank].row_idx = row;
// 		rowbufs[rank][bank].valid = true;
// 	}

// 	/* burst write */
// 	memcpy_with_mask(rowbufs[rank][bank].buf + col, data, BURST_LEN, mask);

// 	/* write back to dram */
// 	memcpy(dram[rank][bank][row], rowbufs[rank][bank].buf, NR_COL);
// }
/*uint32_t cache_write(hwaddr_t addr, size_t len,uint32_t data) {
	uint32_t g = (addr>>6) & 0x7f; //group number
	uint32_t offset = addr & 0x3f; // inside addr
	uint8_t temp[50];
	int i;
	bool v = false;
	for (i = g * 8 ; i < (g+1)*8 ;i ++)
	{
		if (!valid)
			{
				v = true;
				valid = true;
				memcpy (cache + offset,temp,BURST_LEN);
			}
	}
	if (!v)return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
	if (offset + len > BURST_LEN) {
		memcpy(cache + offset + BURST_LEN, temp + BURST_LEN,BURST_LEN);
	}
	return unalign_rw(temp + offset, 4);
}*/
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {

	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	dram_write(addr, len, data);
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

