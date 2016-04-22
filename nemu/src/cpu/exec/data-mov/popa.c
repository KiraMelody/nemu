#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "popa-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "popa-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(popa_n)
