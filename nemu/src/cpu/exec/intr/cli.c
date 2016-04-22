#include "cpu/exec/helper.h"
#include <nemu.h>

make_helper(cli)
{
	cpu.IF = 0;
	return 1;
}