#include <nemu.h>

#define DIR(addr) ((addr)>>22)
#define PAGE(addr) (((addr)>>12) & 0x3ff)
#define OFFSET(addr) ((addr) & 0xfff)

hwaddr_t page_translate(lnaddr_t addr) {
	PAGE_descriptor dir;
	PAGE_descriptor page;
	hwaddr_t hwaddr;
	if (cpu.cr0.paging == 0)return addr;
	//if ((hwaddr = readTLB(addr)) != -1)return hwaddr + OFFSET(addr);
	dir.page_val = hwaddr_read((cpu.cr3.page_directory_base<<12)+(DIR(addr)<<2), 4);
	//Assert(dir.p, "pagevalue = %x eip = %x", dir.page_val,cpu.eip);
	page.page_val = hwaddr_read((dir.addr<<12)+(PAGE(addr)<<2), 4);
	//Assert(page.p, "page do not exist at %x", cpu.eip);
	hwaddr = (page.addr<<12)+OFFSET(addr);
	Assert(0,"value = %x",hwaddr);
	//writeTLB(addr, hwaddr);
	return hwaddr;
}