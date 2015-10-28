#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args) {
	int num=0;
	int str_end=strlen (args); 
	int i;
	for (i=0;i<str_end;i++)
	{
		num=num*10+args[i]-'0';
	}
	if (str_end == 0)num=1;
	cpu_exec(num);
	return 0;
}

static int cmd_info(char *args) {
	int i;
	if (args[0] == 'r') {
	for (i=R_EAX;i<=R_EDI;i++)
	{
		printf ("%s\t0x%08x\n",regsl[i],reg_l(i));
 	}
	printf ("eip\t0x%08x\n",cpu.eip);
 	}
 	else if (args[0] == 'w') {
	
	}
	else assert (0);
	return 0;
}

static int cmd_p(char *args) {
	uint32_t num ;
	bool suc;
	num = expr (args,&suc);
	if (suc)
		printf ("0x%08x\n",num);
	else assert (0);
	return 0;
}
static int cmd_x(char *args) {
	int n;
	swaddr_t start_address;
	int i;
	sscanf (args,"%d %08x",&n,&start_address);
	printf ("0x%08x: ",start_address);
	for (i=1;i<=n;i++)
	{
		printf ("0x%08x ",swaddr_read (start_address,4));
		start_address+=4;
	}
	printf ("\n");
	return 0;	
}
static int cmd_w(char *args) {
	return 0;
}
static int cmd_d(char *args) {
	return 0;
}
static int cmd_bt(char *args) {
	return 0;
}

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	{ "si", "Step into implementation of N instructions after the suspension of execution.When N is notgiven,the default is 1.", cmd_si},
	{ "info", "r for print register state\nw for print watchpoint information", cmd_info},
	{ "p", "Expression evaluation", cmd_p},
	{ "x", "Calculate the value of the expression and regard the result as the starting memory address.", cmd_x},
	{ "w", "Stop the execution of the program if the result of the expression has changed.", cmd_w},
	{ "d", "Delete the Nth watchpoint", cmd_d},
	{ "bt", "Print stack frame chain", cmd_bt}
	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
 	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		printf ("%s\n",cmd);
		if(cmd == NULL) { continue; }
		
		/* treat the remaining string as the arguments,
		 * which may need further parsing
 		 */
		char *args = cmd + strlen(cmd) + 1;
 		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
 			}
 		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
