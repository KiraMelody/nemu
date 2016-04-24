#include "irq.h"

#include <sys/syscall.h>

void add_irq_handle(int, void (*)(void));
void mm_brk(uint32_t);
void serial_printc(char);
int fs_open(const char *, int );
int fs_read(int , void *, size_t);
int fs_write(int, void *, size_t); 
off_t fs_lseek(int , off_t , int);
int fs_close(int);

static void sys_brk(TrapFrame *tf) {
#ifdef IA32_PAGE
	mm_brk(tf->ebx);
#endif
	tf->eax = 0;
}

static void sys_write(TrapFrame *tf)
{
	uint32_t fd = tf->ebx;
    	char *buf = (char *)tf->ecx;
 	uint32_t len = tf->edx;
 	uint32_t result = 0;
 	if (fd == 1 || fd == 2) 
 	{
 	    	while (len--) 
 	    		serial_printc(*(buf++));
        		result = tf->edx;
 	} 
 	else 
 	{
 	    	result = fs_write(fd, buf, len);
 	}
 	tf->eax = result;
}

static void sys_open(TrapFrame *tf) 
{
    	const char *pathname = (const char *)tf->ebx;
    	int flags = tf->ecx;
    	tf->eax = fs_open(pathname, flags);
}

static void sys_close(TrapFrame *tf) 
{
    	int fd = tf->ebx;
    	tf->eax = fs_close(fd);
}

static void sys_read(TrapFrame *tf) 
{
    	int fd = tf->ebx;
    	char *buf = (char *) tf->ecx;
    	size_t len = tf->edx;
    	tf->eax = fs_read(fd, buf, len);
}

static void sys_lseek(TrapFrame *tf) 
{
    	int fd = tf->ebx;
    	off_t offset = tf->ecx;
    	int whence = tf->edx;
    	tf->eax = fs_lseek(fd, offset, whence);
}
void do_syscall(TrapFrame *tf) {
	switch(tf->eax) {
		/* The ``add_irq_handle'' system call is artificial. We use it to 
		 * let user program register its interrupt handlers. But this is 
		 * very dangerous in a real operating system. Therefore such a 
		 * system call never exists in GNU/Linux.
		 */
		case 0: 
			cli();
			add_irq_handle(tf->ebx, (void*)tf->ecx);
			sti();
			break;
		/* TODO: Add more system calls. */
		case SYS_brk: sys_brk(tf); break;
		case SYS_open: sys_open(tf); break;
		case SYS_read: sys_read(tf); break;
		case SYS_write: sys_write(tf); break;
		case SYS_lseek: sys_lseek(tf); break;
		case SYS_close: sys_close(tf); break;

		default: panic("Unhandled system call: id = %d", tf->eax);
	}
}

