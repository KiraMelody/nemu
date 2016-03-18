#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "ljmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "ljmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "ljmp-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(ljmp_i)

