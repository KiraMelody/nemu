#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "jne-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jne-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jne-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(jne_i)

