#ifndef __IRQ_H__
#define __IRQ_H__

#include "common.h"

/* TODO: The decleration order of the members in the ``TrapFrame''
 * structure below is wrong. Please re-orgainize it for the C
 * code to use the trap frame correctly.
 */

typedef struct TrapFrame {
	uint32_t edi, esi, ebp, old_esp, ebx, edx, ecx, eax;
   	int32_t irq;
    	uint32_t error_code, eip, cs, eflags;
} TrapFrame;

#endif
