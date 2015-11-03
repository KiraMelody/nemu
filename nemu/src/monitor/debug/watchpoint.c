#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_list[NR_WP];
static WP *head, *free_;

void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i + 1;//modify original document
		wp_list[i].next = &wp_list[i + 1];
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp()
{
	WP *f;
	f = free_;
	free_ = free_->next;
	f->next = head;
	head = f;
	if (head->next == NULL)printf (" %d yeyeye\n",head->NO);
	return f;
}
void free_wp (WP *wp)
{
	WP *f;
	f = head;
	while (f->next != NULL && f->next->NO != wp->NO)f = f->next;
	if (f->next == NULL)
	{
		printf ("%d\n",f->NO);
		if (head->NO == wp->NO)head = head->next;
		if (head == NULL)printf ("NULL\n");
	}
	else if (f->next->NO == wp->NO)f->next = f->next->next;
	else assert (0);
	if (head == NULL)printf ("OK\n");
	wp->next = free_;
	wp->val = 0;
	wp->expr[0] = '\0';
	free_ = wp;
}
bool check_wp()
{
	WP *f;
	f = head;
	bool key = true;
	bool suc;
	while (f != NULL)
	{
	//	printf ("f -> %d\n",f->NO);
		uint32_t tmp_expr = expr (f->expr,&suc);
		if (!suc)assert (1);
		if (tmp_expr != f->val)
		{
			key = false;
			printf ("Watchpoint %d: %s\n",f->NO,f->expr);
			printf ("Old value = %d\n",f->val);
			printf ("New value = %d\n",tmp_expr);
		}
		f = f->next;
	}
	return key;
}
void delete_wp(int num)
{
	WP *f;
	f = &wp_list[num];
	free_wp (f);
}
void info_wp()
{
	WP *f;
	f=head;
	while (f!=NULL)
	{
		printf ("Watchpoint %d: %s = %d\n",f->NO,f->expr,f->val);
		f = f->next;
	}
}
