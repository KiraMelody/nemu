#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "cmovs-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmovs-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmovs-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(cmovs_r2rm)
make_helper_v(cmovs_rm2r)
