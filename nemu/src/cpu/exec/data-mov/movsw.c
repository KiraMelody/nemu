#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "movsw-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "movsw-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movsw-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(movsw_r2rm)
make_helper_v(movsw_rm2r)

