#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "lea-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "lea-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "lea-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(lea_r2rm)
make_helper_v(lea_rm2r)
