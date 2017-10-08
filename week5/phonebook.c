#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "bt/inc/btree.h"


void menu()
{
  printf("---------------------------------------------------------\n");
  printf("\t\t Phonebook - Btree\n");
  printf("---------------------------------------------------------\n");
  printf(" 1. Print out the list\n 2. Add/Edit a contact\n 3. Search by name\n 4. Search by number\n 5. Delete a contact\n 6. Edit a existing contact\n 7. Quit with saving\n 0. Quit\nChoose one option:");

}

void print_tree(BTA *root)
{
    BTint i;
    char number[20];
    char name[30];
    int rsize;
    btpos(root, ZSTART);
    while(bnxtky(root, name, &i) == 0) {
      if(btsel(root, name, number, 20, &rsize) == 0)
	printf("%-30s%s\n", name, number);
    }
}

void add(BTA *root)
{
  BTint value;
  char name[30], number[20];

  printf("Enter name: "); scanf("%[^\n]s", name); while(getchar()!='\n');
  printf("Enter number: "); scanf("%s", number);
  btpos(root, ZSTART);
  if(bfndky(root, name, &value) == 0)
    {
      strcat(name,"*");
      btins(root, name, number, 20);
    }
  else {
    btins(root, name, number, 20);
  }
  printf("Added successfully !!!\n");
}

void searchByName(BTA *root)
{
  char name[30], number[20];
  int rsize;
  printf("Enter name: "); scanf("%[^\n]s", name); while(getchar()!='\n');
  if(btsel(root, name, number,20, &rsize) == 0)
    printf("+ %s - %s\n", name, number);
  else {
    printf("There's no %s in the list phonebook!!!\n", name);
  }
}

void searchByNumber(BTA *root)
{
  BTint value;
  char name[30], number[20], number1[20];
  int rsize;
  printf("Enter phonenumber: "); scanf("%s", number);
  btpos(root, ZSTART);
  while(bnxtky(root, name, &value) == 0)
    {
      btsel(root, name, number1, 20, &rsize);
      if(strcmp(number, number1) == 0)
	{
	  printf("+ %s - %s\n", name, number);
	  return;
	}
    }

  printf("phonenumber: %s is not in the list!!!\n", number);
  
}

void edit(BTA *root)
{
  char name[30], number[20];
  int rsize;
  printf("Enter name: "); scanf("%[^\n]s", name); while(getchar()!='\n');
   if(btsel(root, name, number, 20, &rsize) == 0)
     {
       printf("Enter phonenumber: "); scanf("%s", number);
       btupd(root,name, number, 20);
       printf("Successful edition !\n");
     }
   else {
     printf("No contact is %s\n",name);
   }
}

void delete(BTA *root)
{
  char name[30];
  printf("Enter name: "); scanf("%[^\n]s", name); while(getchar()!='\n');
  if(btdel(root,name) == 0)
    {
      printf("Deleted the contact!\n");
      
    }
  else {
    printf("No contact is %s\n", name);
  }
}

void save(BTA *root, char *filename)
{
  BTint value;
  char name[30], number[20];
  int rsize;
  btpos(root, ZSTART);
  FILE *f = fopen(filename, "w+");
  while(bnxtky(root, name, &value) == 0)
    {
      btsel(root, name, number, 20, &rsize);
      fprintf(f,"%s\t%s\n",name,number);
    }
  fclose(f);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Syntax: ./phonebook filename\n");
        return 1;
    }
    
    int choose;
    BTA *tree;
    char name[30];
    char number[20];
    btinit();
    tree = btcrt("contact", 0, FALSE);
    FILE *f = fopen(argv[1], "r");
    if(f == NULL)
      {
	printf("File phonebook.txt does not exist!!!\n");
      }
    else {
      while(1)
	{
	  if(feof(f))
	    break;
	  if(fscanf(f,"%[^\t]",name) == EOF)
	    break;
	  fscanf(f,"%*c");
	  fscanf(f,"%[^\n]", number); fscanf(f,"%*c");
	 
	  btins(tree, name, number, 20);
	  printf("%s - %s\n", name, number);
	}
    }
    fclose(f);
    while (choose != 0 || choose != 7) {
      menu();
      scanf("%d", &choose);
      switch(choose) {
      case 0:
	break;
      case 1:
	print_tree(tree);
	break;
	
      case 2:
	while(getchar()!='\n');
	add(tree);
	break;
      case 3:
	while(getchar()!='\n');
	searchByName(tree);
	break;
      case 4:
	while(getchar()!='\n');
	searchByNumber(tree);
	break;
      case 5:
	while(getchar()!='\n');
	delete(tree);
	break;
      case 6:
	while(getchar()!='\n');
	edit(tree);
	break;
      case 7:
	save(tree,argv[1]);
	break;
      default:
	
	printf("Invalid input!!!\nPlease choose ");
	break;
      }
    }
    
    btcls(tree);
    return 0;
}
