#include <nemu.h>

lnaddr_t seg_translate(swaddr_t addr, size_t len, SELECTOR current_sreg) {
	if (cpu.cr0.protect_enable == 0)return addr;
	if (current_sreg.val == cpu.cs.selector) 
	{
		Assert(addr+len < cpu.cs.seg_limit, "cs segment out limit");
		return cpu.cs.seg_base + addr;
	}
	else if (current_sreg.val == cpu.ds.selector) 
	{
		Assert(addr+len < cpu.ds.seg_limit, "ds segment out limit");
		return cpu.ds.seg_base + addr;
	}
	else if (current_sreg.val == cpu.es.selector) 
	{
		Assert(addr+len < cpu.es.seg_limit, "es segment out limit");
		return cpu.es.seg_base + addr;
	}
	else if (current_sreg.val == cpu.ss.selector) 
	{
		Assert(addr+len < cpu.ss.seg_limit, "ss segment out limit");
		return cpu.ss.seg_base + addr;
	}
	else return addr;
	
}
