#include "nemu.h"

#define ENTRY_START 0x100000

extern uint8_t entry [];
extern uint32_t entry_len;
extern char *exec_file;
#define TLB_SIZE 64
extern struct Tlb
{
	bool valid;
	int tag;
	int page_number;
}tlb[TLB_SIZE];

void load_elf_tables(int, char *[]);
void init_regex();
void init_wp_list();
void init_cache();
void init_ddr3();

FILE *log_fp = NULL;

static void init_log() {
	log_fp = fopen("log.txt", "w");
	Assert(log_fp, "Can not open 'log.txt'");
}

static void welcome() {
	printf("Welcome to NEMU!\nThe executable is %s.\nFor help, type \"help\"\n",
			exec_file);
}
static void init_eflags() {
	cpu.eflags = 2;
}

static void init_cr0() {
	cpu.cr0.protect_enable = 0;
	cpu.cr0.paging = 0;
}

static void init_seg() {
	cpu.cs.seg_base = 0x0;
	cpu.cs.seg_limit = 0xffffffff;
}

static void init_tlb() {
	int i;
	for (i = 0;i < TLB_SIZE;i ++) 
	{
	 	tlb[i].valid = false;
	}
}

static void init_lidt() {
	cpu.idtr.base_addr = 0;
	cpu.idtr.seg_limit = 0x3ff;
}

void init_monitor(int argc, char *argv[]) {
	/* Perform some global initialization */

	/* Open the log file. */
	init_log();

	/* Load the string table and symbol table from the ELF file for future use. */
	load_elf_tables(argc, argv);
	/* Compile the regular expressions. */
	init_regex();

	/* Initialize the watchpoint link list. */
	init_wp_list();

	/* Display welcome message. */
	welcome();
}

#ifdef USE_RAMDISK
static void init_ramdisk() {
	int ret;
	const int ramdisk_max_size = 0xa0000;
	FILE *fp = fopen(exec_file, "rb");
	Assert(fp, "Can not open '%s'", exec_file);

	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);
	Assert(file_size < ramdisk_max_size, "file size(%zd) too large", file_size);

	fseek(fp, 0, SEEK_SET);
	ret = fread(hwa_to_va(0), file_size, 1, fp);
	assert(ret == 1);
	fclose(fp);
}
#endif

static void load_entry() {
	int ret;
	FILE *fp = fopen("entry", "rb");
	Assert(fp, "Can not open 'entry'");

	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	ret = fread(hwa_to_va(ENTRY_START), file_size, 1, fp);
	assert(ret == 1);
	fclose(fp);
}

void restart() {
	/* Perform some initialization to restart a program */
#ifdef USE_RAMDISK
	/* Read the file with name `argv[1]' into ramdisk. */
	init_ramdisk();
#endif

	/* Read the entry code into memory. */
	load_entry();

	/* Set the initial instruction pointer. */
	cpu.eip = ENTRY_START;
	init_eflags();
	init_cr0();
	init_seg();
	init_tlb();
	init_lidt();
	/* Initialize CACHE. */
	init_cache();
	/* Initialize DRAM. */
	init_ddr3();
}
