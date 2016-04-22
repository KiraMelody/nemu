#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "cmova-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmova-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmova-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(cmova_r2rm)
make_helper_v(cmova_rm2r)
