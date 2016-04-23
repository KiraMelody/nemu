#include "cpu/helper.h"
#include "cpu/decode/modrm.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);
static make_helper(_2byte_esc);

#define make_group(name, item0, item1, item2, item3, item4, item5, item6, item7) \
	static helper_fun concat(opcode_table_, name) [8] = { \
	/* 0x00 */	item0, item1, item2, item3, \
	/* 0x04 */	item4, item5, item6, item7  \
	}; \
	static make_helper(name) { \
		ModR_M m; \
		m.val = instr_fetch(eip + 1, 1); \
		return concat(opcode_table_, name) [m.opcode](eip); \
	}
	
/* 0x80 */
make_group(group1_b,
	add_i2rm_b, or_i2rm_b, adc_i2rm_b, sbb_i2rm_b, 
	and_i2rm_b, sub_i2rm_b, xor_i2rm_b, cmp_i2rm_b)

/* 0x81 */
make_group(group1_v,
	add_i2rm_v, or_i2rm_v, adc_i2rm_v, sbb_i2rm_v, 
	and_i2rm_v, sub_i2rm_v, xor_i2rm_v, cmp_i2rm_v)

/* 0x83 */
make_group(group1_sx_v,
	add_si2rm_v, or_si2rm_v, adc_si2rm_v, sbb_si2rm_v, 
	and_si2rm_v, sub_si2rm_v, xor_si2rm_v, cmp_si2rm_v)

/* 0xc0 */
make_group(group2_i_b,
	inv, inv, inv, inv, 
	shl_rm_imm_b, shr_rm_imm_b, inv, sar_rm_imm_b)

/* 0xc1 */
make_group(group2_i_v,
	inv, inv, inv, inv, 
	shl_rm_imm_v, shr_rm_imm_v, inv, sar_rm_imm_v)

/* 0xd0 */
make_group(group2_1_b,
	inv, inv, inv, inv, 
	shl_rm_1_b, shr_rm_1_b, inv, sar_rm_1_b)

/* 0xd1 */
make_group(group2_1_v,
	inv, inv, inv, inv, 
	shl_rm_1_v, shr_rm_1_v, inv, sar_rm_1_v)

/* 0xd2 */
make_group(group2_cl_b,
	inv, inv, inv, inv, 
	shl_rm_cl_b, shr_rm_cl_b, inv, sar_rm_cl_b)

/* 0xd3 */
make_group(group2_cl_v,
	inv, inv, inv, inv, 
	shl_rm_cl_v, shl_rm_cl_v, inv, sar_rm_cl_v)

/* 0xf6 */
make_group(group3_b,
	test_i2rm_b, inv, not_rm_b, neg_rm_b, 
	mul_rm_b, imul_rm2a_b, div_rm_b, idiv_rm_b)

/* 0xf7 */
make_group(group3_v,
	test_i2rm_v, inv, not_rm_v, neg_rm_v, 
	mul_rm_v, imul_rm2a_v, div_rm_v, idiv_rm_v)

/* 0xfe */
make_group(group4,
	inv, inv, inv, inv, 
	inv, inv, inv, inv)

/* 0xff */
make_group(group5,
	inv, inv, call_rm_v, call_rm_v, 
	jmp_rm_v, inv, push_rm_v, inv)

make_group(group6,
	inv, inv, inv, inv, 
	inv, inv, inv, inv)

make_group(group7,
	inv, inv, lgdt_rm_v, lidt_rm_v, 
	inv, inv, inv, inv)


/* TODO: Add more instructions!!! */

helper_fun opcode_table [256] = {
/* 0x00 */	add_r2rm_b, add_r2rm_v, add_rm2r_b , add_rm2r_v,
/* 0x04 */	add_i2a_b, add_i2a_v, inv, inv,
/* 0x08 */	or_r2rm_b, or_r2rm_v, or_rm2r_b, or_rm2r_v,
/* 0x0c */	or_i2a_b, or_i2a_v, inv, _2byte_esc,
/* 0x10 */	inv, adc_r2rm_v, inv, inv,
/* 0x14 */	inv, inv, inv, inv,
/* 0x18 */	sbb_r2rm_b, sbb_r2rm_v, sbb_rm2r_b, sbb_rm2r_v,
/* 0x1c */	sbb_i2a_b, sbb_i2a_v, inv, inv,
/* 0x20 */	and_r2rm_b, and_r2rm_v, and_rm2r_b, and_rm2r_v,
/* 0x24 */	and_i2a_b, and_i2a_v, inv, inv,
/* 0x28 */	sub_r2rm_b, sub_r2rm_v, sub_rm2r_b, sub_rm2r_v,
/* 0x2c */	sub_i2a_b, sub_i2a_v, inv, inv,
/* 0x30 */	xor_r2rm_b, xor_r2rm_v, inv, inv,
/* 0x34 */	inv, inv, inv, inv,
/* 0x38 */	cmp_r2rm_b, cmp_r2rm_v, cmp_r2rm_b, cmp_rm2r_v,
/* 0x3c */	cmp_i2a_b, cmp_i2a_v, inv, inv,
/* 0x40 */	inc_r_v, inc_r_v, inc_r_v, inc_r_v,
/* 0x44 */	inc_r_v, inc_r_v, inc_r_v, inc_r_v,
/* 0x48 */	dec_r_v,dec_r_v , dec_r_v, dec_r_v,
/* 0x4c */	dec_r_v,dec_r_v , dec_r_v, dec_r_v,
/* 0x50 */	push_r_v, push_r_v, push_r_v, push_r_v,
/* 0x54 */	push_r_v, push_r_v, push_r_v, push_r_v,
/* 0x58 */	pop_r_v, pop_r_v, pop_r_v, pop_r_v,
/* 0x5c */	pop_r_v, pop_r_v, pop_r_v, pop_r_v,
/* 0x60 */	pusha_n_v, popa_n_v, inv, inv,
/* 0x64 */	inv, inv, data_size, stack_size,
/* 0x68 */	push_i_v, imul_i_rm2r_v, push_i_b, imul_si_rm2r_v,
/* 0x6c */	inv, inv, inv, inv,
/* 0x70 */	jo_i_b, jno_i_b, jb_i_b, jae_i_b,
/* 0x74 */	je_i_b, jne_i_b, jbe_i_b, ja_i_b,
/* 0x78 */	js_i_b, jns_i_b, jp_i_b, jnp_i_b,
/* 0x7c */	jl_i_b, jge_i_b, jle_i_b, jg_i_b,
/* 0x80 */	group1_b, group1_v, inv, group1_sx_v, 
/* 0x84 */	test_r2rm_b, test_r2rm_v, xchg_r2rm_b, xchg_r2rm_v,
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	inv, lea, mov_seg, inv,
/* 0x90 */	nop, xchg_a2r_v, inv, inv,
/* 0x94 */	inv, inv, inv, inv,
/* 0x98 */	cwtl_n_v, cltd_n_v, inv, inv,
/* 0x9c */	inv, inv, inv, inv,
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	movs_n_b, movs_n_v, cmps_n_b, cmps_n_v,
/* 0xa8 */	test_i2a_b, test_i2a_v, stos_n_b, stos_n_v,
/* 0xac */	inv, inv, inv, inv,
/* 0xb0 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb8 */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xc0 */	group2_i_b, group2_i_v, ret_i_v, ret_n_v,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave_n_v, inv, inv,
/* 0xcc */	int3, intr, inv, iret,
/* 0xd0 */	group2_1_b, group2_1_v, group2_cl_b, group2_cl_v,
/* 0xd4 */	inv, inv, nemu_trap, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, inv,
/* 0xe4 */	in_i2a_b, in_i2a_v, out_i2a_b, out_i2a_v,
/* 0xe8 */	call_i_v, jmp_i_v, ljmp, jmp_i_b,
/* 0xec */	in_r2rm_b, in_r2rm_v, out_r2rm_b, out_r2rm_v,
/* 0xf0 */	inv, inv, inv, rep,
/* 0xf4 */	hlt, inv, group3_b, group3_v,
/* 0xf8 */	inv, inv, cli, sti,
/* 0xfc */	cld, std, group4, group5	
};

helper_fun _2byte_opcode_table [256] = {
/* 0x00 */	group6, group7, inv, inv, 
/* 0x04 */	inv, inv, inv, inv, 
/* 0x08 */	inv, inv, inv, inv, 
/* 0x0c */	inv, inv, inv, inv, 
/* 0x10 */	inv, inv, inv, inv, 
/* 0x14 */	inv, inv, inv, inv, 
/* 0x18 */	inv, inv, inv, inv, 
/* 0x1c */	inv, inv, inv, inv, 
/* 0x20 */	mov_cr2r, inv, mov_r2cr, inv, 
/* 0x24 */	inv, inv, inv, inv,
/* 0x28 */	inv, inv, inv, inv, 
/* 0x2c */	inv, inv, inv, inv, 
/* 0x30 */	inv, inv, inv, inv, 
/* 0x34 */	inv, inv, inv, inv,
/* 0x38 */	inv, inv, inv, inv, 
/* 0x3c */	inv, inv, inv, inv, 
/* 0x40 */	inv, inv, inv, inv, 
/* 0x44 */	cmove_rm2r_v, inv, inv, cmova_rm2r_v,
/* 0x48 */	cmovs_rm2r_v, cmovns_rm2r_v, inv, inv, 
/* 0x4c */	inv, cmovge_rm2r_v, inv, inv, 
/* 0x50 */	inv, inv, inv, inv, 
/* 0x54 */	inv, inv, inv, inv,
/* 0x58 */	inv, inv, inv, inv, 
/* 0x5c */	inv, inv, inv, inv, 
/* 0x60 */	inv, inv, inv, inv,
/* 0x64 */	inv, inv, inv, inv,
/* 0x68 */	inv, inv, inv, inv, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	inv, inv, inv, inv,
/* 0x74 */	inv, inv, inv, inv,
/* 0x78 */	inv, inv, inv, inv, 
/* 0x7c */	inv, inv, inv, inv, 
/* 0x80 */	jo_i_v, jno_i_v, jb_i_v, jae_i_v,
/* 0x84 */	je_i_v, jne_i_v, jbe_i_v, ja_i_v,
/* 0x88 */	js_i_v, jns_i_v, jp_i_v, jnp_i_v, 
/* 0x8c */	jl_i_v, jge_i_v, jle_i_v, jg_i_v, 
/* 0x90 */	seto_rm_b, inv, setb_rm_b, inv,
/* 0x94 */	sete_rm_b, setne_rm_b, inv, inv,
/* 0x98 */	sets_rm_b, inv, setp_rm_b, inv, 
/* 0x9c */	inv, inv, inv, inv, 
/* 0xa0 */	inv, inv, inv, inv, 
/* 0xa4 */	shld_i_v, shld_cl_v, inv, inv,
/* 0xa8 */	inv, inv, inv, inv,
/* 0xac */	shrd_i_v, shrd_cl_v, inv, imul_rm2r_v,
/* 0xb0 */	inv, inv, inv, inv, 
/* 0xb4 */	inv, inv, movzx_rm2r_b, movzx_rm2r_w, 
/* 0xb8 */	inv, inv, inv, inv,
/* 0xbc */	inv, inv, movsx_rm2r_b, movsx_rm2r_w,
/* 0xc0 */	inv, inv, inv, inv,
/* 0xc4 */	inv, inv, inv, inv,
/* 0xc8 */	inv, inv, inv, inv,
/* 0xcc */	inv, inv, inv, inv,
/* 0xd0 */	inv, inv, inv, inv,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, inv,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	inv, inv, inv, inv,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, inv,
/* 0xf4 */	inv, inv, inv, inv,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	inv, inv, inv, inv
};

make_helper(exec) {
	ops_decoded.opcode = instr_fetch(eip, 1);
	return opcode_table[ ops_decoded.opcode ](eip);
}

static make_helper(_2byte_esc) {
	eip ++;
	uint32_t opcode = instr_fetch(eip, 1);
	ops_decoded.opcode = opcode | 0x100;
	return _2byte_opcode_table[opcode](eip) + 1; 
}
