#include "cpu/exec/helper.h"
#include <nemu.h>

make_helper(sti)
{
	cpu.IF = 1;
	return 1;
}