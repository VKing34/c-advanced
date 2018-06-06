#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct list{
	elementType1 element;
	struct list *pre;
	struct list *next;
}node1;


node1* makenewnode(elementType1 e)
{
	node1* new = (node1*)malloc(sizeof(node1));
	new->element = e;
	new->pre = NULL;
	new->next = NULL;
	return new;
}

void insertAtHead(elementType1 e,node1 **head,node1 **tail)
{
	if(*head == NULL)
	{
		*head = makenewnode(e);
		*tail = *head;
		return;
	}
	node1* new = makenewnode(e);
	new->next = *head;
	(*head)->pre = new;
	*head = new;
}

void insertAtTail(elementType1 e,node1 **head,node1 **tail)
{
	if(*tail == NULL)
	{
		(*tail) = makenewnode(e);
		*head = *tail;
		return;
	}
	node1* new = makenewnode(e);
	new->pre = (*tail);
	(*tail)->next = new;
	(*tail) = new;
}

void insertAtMid(elementType1 e, node1 **head, node1 **tail)
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
		
	node1 *p = *head;
	for(int i = 0; i< order -2; i++)
	{
		if(p == NULL)
		{
		    insertAtTail(e,head,tail);
			return;
		}
		
		p = p->next;
	}
	node1* new = makenewnode(e);
	new->next = p->next;
	p->next->pre = new;
	new->pre = p;
	p->next = new;
}

void delfirst(node1 **head, node1 **taill)
{
	if(*head == NULL)
	{
		printf("There's nothing to delete!\n");
		return;
	}
	node1 *p = *head;
	*head = (*head)->next;
	(*head)->pre = NULL;
	free(p);
}

void deltail(node1 **head, node1 **tail)
{
	if(*tail == NULL)
	{
		printf("There's nothing to delete!\n");
		return;
	}
	node1 *p = *tail;
	*tail = (*tail)->pre;
	(*tail)->next = NULL;
	free(p);
}

void delAtMid(node1 **head, node1 **tail)
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

	node1 *p = *head;
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

int len(node1 *head)
{
	if(head == NULL)
		return 0;
	else
	{
		int l=0;
		node1 *p = head;
		while(p != NULL)
		{
			p=p->next;
			l++;
		}
		return l;
	}
}

void freeall(node1 **head)
{
	node1 *p;
	while(*head != NULL)
	{
		p=*head;
		(*head)=(*head)->next;
		free(p);
	}
}

