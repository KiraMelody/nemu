#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "cmove-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmove-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmove-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(cmove_r2rm)
make_helper_v(cmove_rm2r)
