#ifndef TYPES_H
#define TYPES_H

typedef struct input_queues
{
	int nq;
	int **queues;
	int *np;
	int *tq;
} input_queues;

typedef struct rr_result
{
	int np;
	int order_n;
	int *order;
	int *turnarounds;
} rr_result;

typedef struct node
{
	int value;
	struct node *next;
} node;

void addfront(struct node** head, int new_val);

int getCount(struct node* head);

int GetNth(struct node* head, int index);

#endif
