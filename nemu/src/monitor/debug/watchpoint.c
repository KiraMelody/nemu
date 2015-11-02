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
	return f;
}
void free_wp (WP *wp)
{
	WP *f;
	f = head;
	while (f->next != NULL && f->next->NO != wp->NO)f = f->next;
	if (f->next == NULL)assert (0);
	f->next = f->next->next;
	wp->next = free_;
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
		uint32_t tmp_expr = expr (f->expr,&suc);
		if (!suc)assert (1);
		if (tmp_expr != f->val)
		{
			key = false;
			printf ("Watchpoint %d: %s\n",f->NO,f->expr);
			printf ("Old value = %d\n",f->val);
			printf ("New value = %d\n",tmp_expr);
			f = f->next;
		}
	}
	return key;
}
