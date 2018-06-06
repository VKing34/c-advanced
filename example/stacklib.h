#include<stdio.h>
#include<stdlib.h>

typedef struct stack{
	stackType element;
	struct stack *next;
}stack;

stack* makenewnode(stackType e)
{
	stack* new = (stack*)malloc(sizeof(stack));
	new->element= e;
	new->next=NULL;
	return new;
}

int empty(stack *top)
{
	if(top == NULL)
		return 1;
	else
		return 0;
}

void push(stackType e,stack **top)
{
	if(*top == NULL)
	{
		(*top) = makenewnode(e);
	}
	else {
		stack* new = makenewnode(e);
		new->next = (*top);
		(*top)=new;
	}
}

stackType pop(stack **top)
{
    stackType p = (*top)->element;
	stack *tmp = (*top);
	(*top) = (*top)->next;
	free(tmp);
	return p;
}

int lenStack(stack *top)
{
	int length = 0;
	stack *p =top;
	while(p != NULL)
	{
		length++;
		p = p->next;
	}
	return length;
}
