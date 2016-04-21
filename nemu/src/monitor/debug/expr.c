#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.  * Type 'man regex' for more information about POSIX regex functions.  */
#include <sys/types.h>
#include <regex.h>

#define max_string_long 32
#define max_token_num 32
enum {
	NOTYPE = 256, EQ , NEQ , AND , OR , MINUS , POINTOR , NUMBER , HNUMBER , REGISTER , MARK

	/* TODO: Add more token types */

};
/*
extern char *strtab;
extern Elf32_Sym *symtab;
extern int nr_symtab_entry;
*/
static struct rule {
	char *regex;
	int token_type;
	int priority;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */
	{"\\b[0-9]+\\b",NUMBER,0},				// number
	{"\\b0[xX][0-9a-fA-F]+\\b",HNUMBER,0},		// 16 number
	{"\\$[a-zA-Z]+",REGISTER,0},				// register
	{"\\b[a-zA-Z_0-9]+" , MARK , 0},		// mark
	{"!=",NEQ,3},						// not equal	
	{"!",'!',6},						// not
	{"\\*",'*',5},						// mul
	{"/",'/',5},						// div
	{"	+",NOTYPE,0},					// tabs
	{" +",NOTYPE,0},					// spaces
	{"\\+",'+',4},						// plus
	{"-",'-',4},						// sub
	{"==", EQ,3},						// equal
	{"&&",AND,2},						// and
	{"\\|\\|",OR,1},						// or
	{"\\(",'(',7},                        // left bracket   
	{"\\)",')',7},                        // right bracket 
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;
	for(i = 0; i < NR_REGEX; i ++) { 
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED); 
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct ttt {
	int type;
	char str[max_string_long];
	int priority;
} Tokens;

Tokens token[max_token_num];
int nr_token;

/*int	regcomp(regex_t *__restrict, const char *__restrict, int);
size_t	regerror(int, const regex_t *__restrict, char *__restrict, size_t);
int	regexec(const regex_t *__restrict, const char *__restrict,
			size_t, regmatch_t [__restrict], int);
void	regfree(regex_t *);*/



static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	nr_token = 0;
	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				char *tmp = e + position + 1;
				int substr_len = pmatch.rm_eo;
//				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */
				switch(rules[i].token_type) {
					case NOTYPE: break;
					case REGISTER:
						token[nr_token].type = rules[i].token_type;
						token[nr_token].priority = rules[i].priority; 
						strncpy (token[nr_token].str,tmp,substr_len-1);
						token [nr_token].str[substr_len-1]='\0';
						nr_token ++;
						break; 
					default:
						token[nr_token].type = rules[i].token_type;
						token[nr_token].priority = rules[i].priority;
						strncpy (token[nr_token].str,substr_start,substr_len);
						token[nr_token].str[substr_len]='\0';
						nr_token ++;
				}
				position += substr_len;
				break;
 			}
 		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
 	}
	return true; 
}
bool check_parentheses (int l,int r)
{
	int i;
	if (token[l].type == '(' && token[r].type ==')')
	{
		int lc = 0, rc = 0;
		for (i = l + 1; i < r; i ++)
		{
			if (token[i].type == '(')lc ++;
			if (token[i].type == ')')rc ++;
			if (rc > lc)return false;	
		}
		if (lc == rc)return true;
	}
	return false;
}
int dominant_operator (int l,int r)
{
	int i,j;
	int min_priority = 10;
	int oper = l;
	for (i = l; i <= r;i ++)
	{
		if (token[i].type == NUMBER || token[i].type == HNUMBER || token[i].type == REGISTER || token[i].type == MARK)
			continue;
		int cnt = 0;
		bool key = true;
		for (j = i - 1; j >= l ;j --)
		{ 
			if (token[j].type == '(' && !cnt){key = false;break;}
			if (token[j].type == '(')cnt --;
			if (token[j].type == ')')cnt ++; 
		}
		if (!key)continue;
		if (token[i].priority <= min_priority){min_priority = token[i].priority;oper = i;}
 	}
	return oper;
}
uint32_t eval(int l,int r) {
	if (l > r){Assert (l>r,"something happened!\n");return 0;}
	if (l == r) {
	uint32_t num = 0;
	if (token[l].type == NUMBER)
		sscanf(token[l].str,"%d",&num);
	if (token[l].type == HNUMBER)
		sscanf(token[l].str,"%x",&num);
	if (token[l].type == REGISTER)
		{
			if (strlen (token[l].str) == 3) {
			int i;
			for (i = R_EAX; i <= R_EDI; i ++)
				if (strcmp (token[l].str,regsl[i]) == 0)break;
				if (i > R_EDI)
				if (strcmp (token[l].str,"eip") == 0)
					num = cpu.eip;
				else Assert (1,"no this register!\n");
			else num = reg_l(i);
 			}
 			else if (strlen (token[l].str) == 2) {
 			if (token[l].str[1] == 'x' || token[l].str[1] == 'p' || token[l].str[1] == 'i') {
				int i;
				for (i = R_AX; i <= R_DI; i ++)
					if (strcmp (token[l].str,regsw[i]) == 0)break;
				num = reg_w(i);
			}
 			else if (token[l].str[1] == 'l' || token[l].str[1] == 'h') {
				int i;
				for (i = R_AL; i <= R_BH; i ++)
					if (strcmp (token[l].str,regsb[i]) == 0)break;
				num = reg_b(i);
			}
			else assert (1);
			}
		}
	if (token[l].type == MARK)
	{
		int i;
		for (i=0;i<nr_symtab_entry;i++)
		{
			if ((symtab[i].st_info&0xf) == STT_OBJECT)
			{
				char tmp [max_string_long];
				int tmplen = symtab[i+1].st_name - symtab[i].st_name - 1;
				strncpy (tmp,strtab+symtab[i].st_name,tmplen);
				tmp [tmplen] = '\0';
				if (strcmp (tmp,token[l].str) == 0)
				{
					num = symtab[i].st_value;
				}
			}
		}
	}
		return num;
	}
	else if (check_parentheses (l,r) == true)return eval (l + 1,r - 1);
 	else {
		int op = dominant_operator (l,r);
//		printf ("op = %d\n",op);
 		if (l == op || token [op].type == POINTOR || token [op].type == MINUS || token [op].type == '!')
		{
			uint32_t val = eval (l + 1,r);
//			printf ("val = %d\n",val);
			switch (token[l].type)
 			{
				case POINTOR:current_sreg = R_DS;return swaddr_read (val,4);
				case MINUS:return -val;
				case '!':return !val;
				default :Assert (1,"default\n");
			} 
		}

		uint32_t val1 = eval (l,op - 1);
		uint32_t val2 = eval (op + 1,r);
//		printf ("1 = %d,2 = %d\n",val1,val2);
		switch (token[op].type)
		{
			case '+':return val1 + val2;
			case '-':return val1 - val2;
			case '*':return val1 * val2;
			case '/':return val1 / val2;
			case EQ:return val1 == val2;
			case NEQ:return val1 != val2;
			case AND:return val1 && val2;
			case OR:return val1 || val2;
			default:
			break;
  		}
  	}
	assert (1);
	return -123456;
}
uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
  	}
	int i;
	for (i = 0;i < nr_token; i ++) {
 		if (token[i].type == '*' && (i == 0 || (token[i - 1].type != NUMBER && token[i - 1].type != HNUMBER && token[i - 1].type != REGISTER && token[i - 1].type != MARK && token[i - 1].type !=')'))) {
			token[i].type = POINTOR;
			token[i].priority = 6;
		}
		if (token[i].type == '-' && (i == 0 || (token[i - 1].type != NUMBER && token[i - 1].type != HNUMBER && token[i - 1].type != REGISTER && token[i - 1].type != MARK && token[i - 1].type !=')'))) {
			token[i].type = MINUS;
			token[i].priority = 6;
 		}
  	}
	/* TODO: Insert codes to evaluate the expression. */	
	*success = true;
	return eval (0,nr_token-1);
}

