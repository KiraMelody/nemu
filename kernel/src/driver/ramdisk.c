#include "common.h"
#include <string.h>

#define RAMDISK_START ((void *)0)

/* The kernel is monolithic, therefore we do not need to
 * translate the address ``buf'' from the user process to
 * a physical one, which is necessary for a microkernel.
 */
void ramdisk_read(uint8_t *buf, uint32_t offset, uint32_t len) {
	memcpy(buf, RAMDISK_START + offset, len);
}

void ramdisk_write(uint8_t *buf, uint32_t offset, uint32_t len) {
	memcpy(RAMDISK_START + offset, buf, len);
}

