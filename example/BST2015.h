# define MAX_NODE_BST 100
# define LEFT 0
# define RIGHT 1
int height = 0;
int ElementLength = 10;
int last[1611];
int needline[1611];
#include<stdio.h>
#include<stdlib.h>
#include <string.h>


typedef struct tree_t{
	elementType key;   
	struct tree_t* right;
	struct tree_t* left;
}node;



void makeNullTree(node* root){
	if(root == NULL) return;
	makeNullTree(root->left);
	makeNullTree(root->right);
	free(root);
}

node* makeNewTree(elementType data){
	node* new = (node*)malloc(sizeof(node));

    new->key = data;
   
	new->left = NULL;
	new->right = NULL;
	
	return new;
}

int isLeaf(node* node){
	return(node->left == NULL && node->right == NULL);
}

int countLeaf(node* root){
	if(root == NULL) return 0;
	if(isLeaf(root)) return 1;
	return countLeaf(root->left) + countLeaf(root->right);
}

int heightTree(node* root){
	if(root == NULL)
		return 0;
	int h = 0;
	int h_left = heightTree(root->left);
	int h_right = heightTree(root->right);

	return (h_left > h_right) ? (h_left+1) : (h_right+1);
}

int internalNode(node* root){
	if(root == NULL) return 0;
	if(isLeaf(root)) return 0;
	return 1 + internalNode(root->left) + internalNode(root->right);
}

node* findMIN(node* root){
	if(root == NULL) return NULL;
	if(isLeaf(root) || root->left == NULL) return root;
	else return findMIN(root->left);
}

node* findMAX(node* root){
	if(root == NULL) return NULL;
	if(isLeaf(root) || root->right == NULL) return root;
	else return findMAX(root->right);
}

int compareName(char* s1, char* s2){
	char buff1[30];
	char buff2[30];
	int i = strlen(s1);
	int j = strlen(s2);
	int check = 0;

	while(i >= 0 && j >= 0 && check == 0){
		while(s1[i] != ' ' && i >= 0)
			i--;
		while(s2[j] != ' ' && j >= 0)
			j--;
		strncpy(buff1, s1 + i + 1, strlen(s1)-i+1);
		strncpy(buff2, s2 + j + 1, strlen(s2)-j+1);
		check = strcmp(buff1, buff2);
		if(check > 0) return 1;
		else if(check < 0) return -1;
		i--;
		j--;
	}
	if(i >= 0) return 1;
	if(j >= 0) return -1;
	return 0;	
}

void insertNode(node **root, elementType data){


	node* new = makeNewTree(data);
	node *p = *root;
	if(p == NULL)
	{
		(*root) = new;
		return;
	}
	while(1)
	{
		if(p->key.id >= data.id)
		{
			if(p->left == NULL)
			{
				p->left = new;
				return;
			}
			else
				p = p->left;
		}
		else
		{
			if(p->right == NULL)
			{
				p->right= new;
				return;
			}
			else
				p = p->right;
			
		}
	}

	
}

node* findNode(node* root, elementType data)
{
	if(root == NULL)
		return NULL;
	if(root->key.id > data.id)
		return findNode(root->left,data);
	else if(root->key.id < data.id)
		return findNode(root->right,data);
	else {
		return root;
	}
	
}


void search(node **root, elementType data, node **parent, node **x, int *found)
{
	node *q;
	q = *root;
	*found = 0;
	*parent = NULL;
	while (q != NULL)
	{
		if(q->key.id == data.id)
		{
			*found = 1;
			*x = q;
			return;
		}
		*parent = q;
		if(q->key.id < data.id)
			q = q->right;
		else {
			q = q->left;
		}
	}
}

void deleteNode(node** root, elementType data)
{
	int found;
	node *parent, *x, *xsucc;
	if(*root == NULL)
	{
		printf("Tree is empty!!!\n");
		return;
	}

	parent = x = NULL;
	search(root, data, &parent, &x, &found);
	if(found == 0)
	{
		printf("The node doesn't exist!!!\n");
		return;
	}
	if(x->left != NULL && x->right != NULL)
	{
		parent = xsucc;
		xsucc = xsucc->right;
		while (xsucc-> left != NULL) {
			parent = xsucc;
			xsucc = xsucc->left;
		}
	    
		x->key = xsucc->key;
		x = xsucc;
	}
	if(x->left == NULL && x->right == NULL)
	{
		if(parent->right == x)
			parent->right = NULL;
		else {
			parent->left = NULL;
		}
		free(x);
		return;
	}
	if(x->left == NULL && x->right != NULL)
	{
		if(parent->left == x)
			parent->left = x->right;
		else {
			parent->right = x->right;
		}
		free(x);
		return;
	}
	if(x->left != NULL && x->right == NULL)
	{
		if(parent->left == x)
			parent->left = x->left;
		else
			parent->right = x->left;
		free(x);
		return;
	}
}

void freeTree(node** root){
	if(*root != NULL){
		freeTree(&(*root)->left);
		freeTree(&(*root)->right);
		free(*root);
		*root=NULL;			
	}
}

void printNode(elementType data)
{
  printf("%10s",data.toy);
}


void moveto(int l)
{
  for (int i = l; i < height; i++)
    {
      for (int j=0; j<ElementLength; j++) printf(" ");
      printf("  ");
    }
  //getchar();
}

void fill(int l)
{
  for (int i=l-2; i>=0; i--)
    {
      for (int j=0; j<ElementLength; j++) printf(" ");
      printf(" ");
      if (needline[i] == 1) printf("%s","\u2502");
      else printf(" ");
    }
}



void draw(node *p,node *parent,int h,int pos)
{
  if (p == NULL) return;
  if (h == height)
    {
      printf(" ");
      printNode(p->key);
      if (parent != NULL)
	{
	  printf("%s","\u2500");
	  if (p == parent->left)
	    printf("%s","\u2510");
	  else if (p == parent->right)
	    printf("%s","\u2518");
	}
      if (pos == LEFT && last[h-1] == 0) needline[h-1] = 1; else
	if (pos == RIGHT && last[h-1] == 1) needline[h-1] = 0;
      fill(h);
      printf("\n");
      return;
    }
  last[h] = 0;
  needline[h] = 0;
  if (pos == RIGHT && last[h-1] == 1) needline[h-1] = 1; else if (pos == LEFT && last[h-1] == 0) needline[h-1] = 0;
  draw(p->left,p,h+1,LEFT);
  last[h] = 1;
  moveto(h);
  if (p->left != NULL && p->right != NULL) printf("%s","\u251C");
  else if (p->left == NULL && p->right != NULL) printf("%s","\u250C");
  else if (p->left != NULL && p->right == NULL) printf("%s","\u2514");
  else printf(" ");
  printNode(p->key);
  if (parent != NULL)
      {
	printf("%s","\u2500");
	if (p == parent->left)
          printf("%s","\u2510");
	else if (p == parent->right)
          printf("%s","\u2518");
      }
  last[h]=1;
  if (pos == LEFT && last[h-1] == 0) needline[h-1] = 1; else if (pos == RIGHT && last[h-1] == 1) needline[h-1] = 0;
  fill(h);
  printf("\n");
  draw(p->right,p,h+1,RIGHT);
  needline[h] = 0;
}

void drawTree(node *tree)
{
	height = heightTree(tree);
	draw(tree,NULL,0,-1);
}


/* void printInOrder(node* root){ */
/* 	if(root != NULL){ */
/* 		printInOrder(root->left); */
/* 		printf("%s\n", root->name); */
/* 		printInOrder(root->right); */
/* 	} */
/* } */

/* void printPreOrder(node* root){ */
/* 	if(root != NULL){ */
/* 		printf("%s\n", root->name); */
/* 		printInOrder(root->left); */
/* 		printInOrder(root->right); */
/* 	} */
/* } */

/* void printPostOrder(node* root){ */
/* 	if(root != NULL){ */
/* 		printInOrder(root->left); */
/* 		printInOrder(root->right); */
/* 		printf("%s\n", root->name); */
/* 	} */
/* } */
 
