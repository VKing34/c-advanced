#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct list{
	elementType element;
	struct list *pre;
	struct list *next;
}node;


node* makenewnode(elementType e)
{
	node* new = (node*)malloc(sizeof(node));
	new->element = e;
	new->pre = NULL;
	new->next = NULL;
	return new;
}

void insertAtHead(elementType e,node **head,node **tail)
{
	if(*head == NULL)
	{
		*head = makenewnode(e);
		*tail = *head;
		return;
	}
	node* new = makenewnode(e);
	new->next = *head;
	(*head)->pre = new;
	*head = new;
}

void insertAtTail(elementType e,node **head,node **tail)
{
	if(*tail == NULL)
	{
		(*tail) = makenewnode(e);
		*head = *tail;
		return;
	}
	node* new = makenewnode(e);
	new->pre = (*tail);
	(*tail)->next = new;
	(*tail) = new;
}

void insertAtMid(elementType e, node **head, node **tail)
{
	int order;
	{
		printf("Enter the position you want to insert: "); scanf("%d", &order);
	}
	if(*head == NULL || order <= 1)
	{
		insertAtHead(e,head,tail);
		return;
	}
		
	node *p = *head;
	for(int i = 0; i< order -2; i++)
	{
		if(p == NULL)
		{
		    insertAtTail(e,head,tail);
			return;
		}
		
		p = p->next;
	}
	node* new = makenewnode(e);
	new->next = p->next;
	p->next->pre = new;
	new->pre = p;
	p->next = new;
}

void delfirst(node **head, node **taill)
{
	if(*head == NULL)
	{
		printf("There's nothing to delete!\n");
		return;
	}
	node *p = *head;
	*head = (*head)->next;
	(*head)->pre = NULL;
	free(p);
}

void deltail(node **head, node **tail)
{
	if(*tail == NULL)
	{
		printf("There's nothing to delete!\n");
		return;
	}
	node *p = *tail;
	*tail = (*tail)->pre;
	(*tail)->next = NULL;
	free(p);
}

void delAtMid(node **head, node **tail)
{
	if(*head == NULL)
	{
		printf("There's nothing to delete!!!\n");
		return;
	}
	int order;
	{
		printf("Enter the position you want to delete: "); scanf("%d", &order);
	}
	if(order <= 1)
	{
		delfirst(head,tail);
		return;
	}

	node *p = *head;
	for(int i = 0; i< order -1; i++)
	{
		if(p->next == NULL)
		{
		    deltail(head,tail);
			return;
		}
		p = p->next;
	}
	p->pre->next = p->next;
	p->next->pre = p->pre;
	free(p);
}

int len(node *head)
{
	node *p = head;
	int l = 0;
	while(p != NULL)
	{	
		p = p->next;
		l++;
	}
	return l;
}


void freeall(node **head)
{
	node *p;
	while(*head != NULL)
	{
		p=*head;
		(*head)=(*head)->next;
		free(p);
	}
}

