#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "cmovge-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmovge-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmovge-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(cmovge_r2rm)
make_helper_v(cmovge_rm2r)
