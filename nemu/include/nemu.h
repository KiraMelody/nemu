#ifndef __NEMU_H__
#define __NEMU_H__

#include "common.h"
#include "memory/memory.h"
#include "cpu/reg.h"
#include <elf.h>
extern char *strtab;
extern Elf32_Sym *symtab;
extern int nr_symtab_entry;

#endif
