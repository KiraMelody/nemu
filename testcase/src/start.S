.globl start
start:
# Set up a stack for C code. After the kernel is 
# introduced, the following code will never be executed.
	movl $0, %ebp
	movl $(128 << 20), %esp
	subl $16, %esp		# keep the `bt' command happy
	call main			# never return
