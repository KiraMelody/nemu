#include "cpu/exec/helper.h"

make_helper(cld)
{
	cpu.DF = 0;
	return 1;
}
