


typedef struct
{
	int coef;
	int exp;
}elementType1;

#include"string_ext.h"

#include"doublelib.h"

node1 *head, *tail;
node1 *head2, *tail2;



void read()
{
	FILE *fin = fopen("poly.txt","r");
	if(fin == NULL)
	{
		printf("Can't open B.txt!!!\n"); 
		return;
	}
	elementType1 n;
	while(1)
	{
		if(feof(fin)) 
			break;
		fscanf(fin, "%d", &n.coef);
		if(n.coef == -1)
			break;
		fscanf(fin,"%d",&n.exp);
		insertAtTail(n, &head, &tail);
	}
	while(1)
	{
		if(feof(fin))
			break;
		if(fscanf(fin,"%d",&n.coef) == EOF)
			break;
		if(n.coef == -1)
			break;
		if(fscanf(fin,"%d",&n.exp) == EOF)
			break;
		insertAtTail(n,&head2,&tail2);
	}

	fclose(fin); 
	printf("------------Sucessfull---------------------\n");
}

void show()
{
	node1 *p = head;
	printf("P = ");
	while (p != NULL)
	{
		if(p == head && p->element.coef >= 0)
		{
		    printf("%dx^%d(%d) ", p->element.coef, p->element.exp,p);
		}
		else if(p->element.coef >= 0)
			printf("+ %dx^%d(%d) ", p->element.coef,p->element.exp);
		else
			printf("%dx^%d(%d) ",p->element.coef,p->element.exp );
		p = p->next;
	}
	printf("\n");
	p = head2;
	printf("Q = ");
	while (p != NULL)
	{
		if(p == head2 && p->element.coef >= 0)
		{
		    printf("%dx^%d(%d) ", p->element.coef, p->element.exp);
		}
		else if(p->element.coef >= 0)
			printf("+ %dx^%d(%d) ", p->element.coef,p->element.exp);
		else
			printf("%dx^%d(%d) ",p->element.coef,p->element.exp );
		p = p->next;
	}
	printf("\n");
}

void correct()
{
	int len1 = len(head);
	elementType1 list1[len1];
	int i= 0;
	node1 *p = head;
	for(i=0;i<len1 ; i++)
	{
		list1[i]=p->element;
		p=p->next;
	}
	quickSort(list1,0,len1-1);

    freeall(&head);
	head =NULL;
	tail = NULL;
	i = 0;
	elementType1 n;
 
	for(i = len1-1; i > -1; i--)
	{
		if(list1[i].exp == list1[i-1].exp)
		{
			n.coef = list1[i].coef + list1[i-1].coef;
			n.exp = list1[i].exp;
			i--;
			insertAtTail(n,&head,&tail);
		}
		else {
			n = list1[i];
			insertAtTail(n,&head,&tail);
		}
    
	    
	}
	
	p = head;
	printf("P = ");
	while (p != NULL)
	{
		if(p == head && p->element.coef >= 0)
		{
		    printf("%dx^%d(%d) ", p->element.coef, p->element.exp,p);
		}
		else if(p->element.exp == 0)
		{
			printf("+ %d", p->element.coef);
		}
		else if(p->element.coef > 1)
			printf("+ %dx^%d(%d) ", p->element.coef,p->element.exp);
		else if(p->element.coef == 1)
			printf("+ x^%d ", p->element.exp);
		else if(p->element.exp == 0)
		{
			printf("%d", p->element.coef);
		}
		else
			printf("%dx^%d(%d) ",p->element.coef,p->element.exp );
		p = p->next;
	}
	printf("\n");

	// 2

	int len2 = len(head2);
	elementType1 list2[len2];
	i= 0;
	p = head2;
	for(i=0;i<len2 ; i++)
	{
		list2[i]=p->element;
		p=p->next;
	}
	quickSort(list2,0,len2-1);

    freeall(&head2);
	head2 =NULL;
	tail2 = NULL;
	i = 0;

 
	for(i = len2-1; i > -1; i--)
	{
		if(list2[i].exp == list2[i-1].exp)
		{
			n.coef = list2[i].coef + list2[i-1].coef;
			n.exp = list2[i].exp;
			i--;
			insertAtTail(n,&head2,&tail2);
		}
		else {
			n = list2[i];
			insertAtTail(n,&head2,&tail2);
		}
    
	    
	}
	
	p = head2;
	printf("Q = ");
	while (p != NULL)
	{
	    
		if(p == head && p->element.coef >= 0)
		{
		    printf("%dx^%d(%d) ", p->element.coef, p->element.exp,p);
		}
		else if(p->element.exp == 0)
		{
			printf("+ %d", p->element.coef);
		}
		else if(p->element.coef >= 0)
			printf("+ %dx^%d(%d) ", p->element.coef,p->element.exp);
		else if(p->element.coef == 1)
			printf("+ x^%d ", p->element.exp);
		
		else
			printf("%dx^%d(%d) ",p->element.coef,p->element.exp );
		p = p->next;
	}
	printf("\n");
	
}

void merge()
{
	node1 *rhead, *rtail;
	node1 *i = head;
	node1 *j = head2;
	elementType1 n;
	while (i == NULL && j == NULL)
	{
		if(i->element.exp > j->element.exp)
		{
			insertAtTail(i->element,&rhead, &tail);
			insertAtTail(j->element,&rhead, &tail);
			i = i->next;
			j = j->next;
		}
		else if(i->element.exp < j->element.exp)
		{
			insertAtTail(j->element,&rhead, &tail);
			insertAtTail(i->element,&rhead, &tail);
			i = i->next;
			j = j->next;
		}
		else if(i->element.exp == j->element.exp)
		{
			n.coef = i->element.coef + i->element.exp;
			n.exp = i->element.exp;
			i = i->next;
			j = j->next;	
		}
	}
	node1 *p = rhead;
	printf("R = ");
	while (p != NULL)
	{
	    
		if(p == head && p->element.coef >= 0)
		{
		    printf("%dx^%d(%d) ", p->element.coef, p->element.exp,p);
		}
		else if(p->element.exp == 0)
		{
			printf("+ %d", p->element.coef);
		}
		else if(p->element.coef >= 0)
			printf("+ %dx^%d(%d) ", p->element.coef,p->element.exp);
		else if(p->element.coef == 1)
			printf("+ x^%d ", p->element.exp);
		
		else
			printf("%dx^%d(%d) ",p->element.coef,p->element.exp );
		p = p->next;
	}
	printf("\n");
}


void main()
{
	int x;
	while (x != 5)
	{
		printf("------------------------------------------------\n");
		printf("\t              Menu\n");
		printf("------------------------------------------------\n");
		printf("1. Read\n2. Show\n3. Correct\n4. Merge\n5. Exit\nChoose one option: "); scanf("%d", &x);

		/* while(getchar()!='\n'); */
		 switch (x) {
		case 1: 
			read();
			break;
		
		case 2:
			show();
			break;
		case 3:
			correct();
			break;
		case 4:
			merge();
			
			break;
		case 5:
		   
			break;
    
		default:
			printf("Please try again!!!\n");
			break;		
		}
	}

	
	freeall(&head);
	freeall(&head2);
}
