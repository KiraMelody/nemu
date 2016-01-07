testcase_CFLAGS_EXTRA := -m32 -fno-builtin -fno-stack-protector \
						-I$(LIB_COMMON_DIR) -I$(NEWLIBC_DIR)/include

$(eval $(call make_common_rules,testcase,$(testcase_CFLAGS_EXTRA)))

# redefine testcase_BIN
testcase_BIN := $(testcase_COBJS:.o=)
testcase_START_OBJ := $(testcase_OBJ_DIR)/start.o
testcase_LDFLAGS := -m elf_i386 -e start -Ttext=0x00100000 

$(testcase_BIN): % : $(testcase_START_OBJ) %.o $(FLOAT) $(NEWLIBC)
	$(call make_command, $(LD), $(testcase_LDFLAGS), ld $@, $^)
	@objdump -d $@ > $@.txt

$(testcase_OBJ_DIR)/mov: % : %.o
	$(call make_command, $(LD), $(testcase_LDFLAGS), ld $@, $^)
	@objdump -d $@ > $@.txt
