# define MAX_NODE_BST 100
# define LEFT 0
# define RIGHT 1
int height = 0;
int ElementLength = 5;
int last[1611];
int needline[1611];
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct BST{
	elementType key;
	struct BST *left, *right, *parent;
}node;

int max(int a, int b)
{
	return a>b?a:b;
}

node* makeNewNode(elementType data)
{
	node *new = (node*)malloc(sizeof(node));
	new->key = data;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void insertNode(node **root,elementType data)
{
	node *p = *root;
	node *new = makeNewNode(data);
	if(p == NULL)
	{
		*root = new;
		return;
	}
	while (1) {
		if(data < p->key)
		{
			if(p->left == NULL)
			{
				new->parent = p;
				p->left = new;
				return;
			}
			else
				p = p->left;
		}
		else {
			if(p->right == NULL)
			{
				new->parent = p;
				p->right = new;
				return;
			}
			else {
				p = p->right;
			}
		}
		
	}
}

node* findLeftMost(node *tree)
{
	if(tree->left != NULL)
		return findLeftMost(tree->left);
	else {
		return tree;
	}
}

node* findRightMost(node *tree)
{
	if(tree->right != NULL)
		return findRightMost(tree->right);
	else {
		return tree;
	}
}

void deleteNode(node **root,node *d)
{
	if(d == NULL)
		return;
	node *p;
	int t = 0;
	if(d->right != NULL)
	{
		p = findLeftMost(d->right);
		t = 0;
	}
	else if(d->left != NULL)
	{
		p = findRightMost(d->left);
		t = 1;
	}
	if(p == NULL)
	{
		if(d->parent == NULL)
		{
			free(d);
			*root = NULL;
			return;
		}
		else {
			if(d->key < d->parent->key)
				d->parent->left = NULL;
			else
				d->parent->right = NULL;
			free(d);
			return;
			
		}
	}
	if(t == 0)
	{
		if(p->parent == d)
			p->parent->right = p->right;
		else
			p->parent->left = p->right;
		if(p->right != NULL)
			p->right->parent = p->parent;
	}
	else
		if(t == 1)
		{
			if(p->parent == d)
				p->parent->left = p->left;
			else
				p->parent->right = p->left;
			if(p->left != NULL)
				p->left->parent = p->parent;
		}
	d->key = p->key;
	free(p);
}

node* findNode(node *root, elementType data)
{
	if(root == NULL)
		return NULL;
	if(data < root->key)
		return findNode(root->left,data);
	else if(data > root->key)
		return findNode(root->right,data);
	else
		return root;
	
}

void freeTree(node *root)
{
	if(root == NULL)
		return;
	free(root->left);
	free(root->right);
	free(root);
}

int getHeight(node *tree)
{
	if(tree == NULL) return 0;
	if(tree->left == NULL && tree->right == NULL)
		return 0;
	return max(getHeight(tree->left),getHeight(tree->right))+1;
}

void printNode(elementType data)
{
  printf("%*d",ElementLength,data);
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
	height = getHeight(tree);
	draw(tree,NULL,0,-1);
}
