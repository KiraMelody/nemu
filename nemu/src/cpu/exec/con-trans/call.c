#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "call-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */
make_helper_v(call_i)
make_helper_v(call_rm)
