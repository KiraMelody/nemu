#include "cpu/exec/helper.h"

#define DATA_BYTE 1


#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper(std)
{
	cpu.DF = 1;
	print_asm("std");
	return 1;
}