#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "jno-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jno-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jno-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(jno_i)

