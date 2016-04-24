#include <nemu.h>
#include <stdlib.h>
#define TLB_SIZE 64
struct Tlb
{
	bool valid;
	int tag;
	int page_number;
}tlb[TLB_SIZE];
hwaddr_t TLB_read(uint32_t addr)
{
	int va = addr & 0xfffff000;
	int i;
	for (i = 0;i < TLB_SIZE; i ++)
	{
		if (va == tlb[i].tag && tlb[i].valid)
		{
			return tlb[i].page_number;
		}
	}
	return -1;
}
void TLB_write(uint32_t addr,uint32_t num)
{
	int va = addr & 0xfffff000;
	int na = num & 0xfffff000;
	int i;
	for (i = 0;i < TLB_SIZE; i ++)
	{
		if (!tlb[i].valid)
		{
			tlb[i].valid = true;
			tlb[i].tag = va;
			tlb[i].page_number = na;
			return;
		}
	}
	srand (0);
	i = rand()%TLB_SIZE;
	tlb[i].valid = true;
	tlb[i].tag = va;
	tlb[i].page_number = na;
	return;
}

