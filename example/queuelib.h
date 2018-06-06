#include<stdio.h>
#include<stdlib.h>

typedef struct list{
	queueType element;
	struct list *pre;
	struct list *next;
}queue;

int empty(queue **head, queue **tail)
{
	return ((*head) == NULL);
}
void makenullqueue(queue **head, queue **tail)
{
	(*head) = NULL;
	(*tail) = NULL;
}

queue* makenewnode(queueType e)
{
	queue* new = (queue*)malloc(sizeof(queue));
	new->element = e;
	new->pre = NULL;
	new->next = NULL;
	return new;
}

void enqueue(queueType e,queue **head,queue **tail)
{
	if(*head == NULL)
	{
		*head = makenewnode(e);
		*tail = *head;
		return;
	}
	queue* new = makenewnode(e);
	new->next = *head;
	(*head)->pre = new;
	*head = new;
}

void insertAtTail(queueType e,queue **head, queue **tail)
{
if(*tail== NULL)
{
*tail = makenewnode(e);
*head = *tail;
}

queue *new = makenewnode(e);
new->pre = (*tail);
(*tail)->next = new;
(*tail) = new;
}


queueType dequeue(queue **head, queue **tail)
{   
	if(*tail == *head)
	{
		queueType x; x = (*tail)->element;
	    makenullqueue(head,tail);
		return x;
	}
	queueType x = (*tail)->element;
	queue *p = *tail;
	*tail = (*tail)->pre;
	(*tail)->next = NULL;
	free(p);
	return x;
	
}

void delfirst(queue **head, queue **tail)
{
	if(*head == NULL)
	{
		printf("There's nothing to delete!\n");
		return;
	}
	if(*head == *tail)
{
free(*head);
(*head)=NULL;
(*tail)=NULL;
return;
}
	queue *p = *head;
	*head = (*head)->next;
	(*head)->pre = NULL;
	free(p);
}

void deltail(queue **head, queue **tail)
{
	if(*tail == NULL)
	{
		printf("There's nothing to delete!\n");
		return;
	}
	queue *p = *tail;
	*tail = (*tail)->pre;
	(*tail)->next = NULL;
	free(p);
}

void delpoint(queue **p, queue **head, queue **tail)
{
	if(*head == *tail)
	{
		free(*p);
		(*head)=NULL;
		(*tail)=NULL;
		return;
	}
	if(*p == *head)
	{
		delfirst(head,tail);
		return;
	}
        if(*p == *tail)
	{
		deltail(head,tail);
		return;
	}
	
	(*p)->pre->next = (*p)->next;
	(*p)->next->pre = (*p)->pre;
	free(*p);
	
}

void delatmid(int order,queue **head, queue **tail)
{
	if(*tail == NULL)
	{
		printf("There's nothing to delete!!!\n");
		return;
	}
    if(order <= 1)
	{
		deltail(head,tail);
		return;
	}

	queue *p = *tail;
	for(int i = 0; i< order -1; i++)
	{
		if(p->next == NULL)
		{
		    delfirst(head,tail);
			return;
		}
		p = p->next;
	}
	p->pre->next = p->next;
	p->next->pre = p->pre;
	free(p);
}

int len(queue *head)
{
	if(head == NULL)
		return 0;
	else
	{
		int l=0;
		queue *p = head;
		while(p != NULL)
		{
			p=p->next;
			l++;
		}
		return l;
	}
}
void freeall(queue **head)
{
	queue *p;
	while(*head != NULL)
	{
		p=*head;
		(*head)=(*head)->next;
		free(p);
	}
}
