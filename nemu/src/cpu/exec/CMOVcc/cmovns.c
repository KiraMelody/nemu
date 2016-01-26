#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "cmovns-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmovns-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmovns-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(cmovns_r2rm)
make_helper_v(cmovns_rm2r)
