#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
#include"jval.h"

void menu()
{
  printf("---------------------------------------------------------\n");
  printf("\t\t Phonebook - Btree\n");
  printf("---------------------------------------------------------\n");
   printf(" 1. Print out the list\n 2. Add/Edit a contact\n 3. Search by name\n 4. Search by number\n 5. Delete a contact\n 6. Edit a existing contact\n 7. Quit with saving\n 0. Quit\nChoose one option:");
}


void print_book(JRB book)
{
  JRB p;
  jrb_traverse(p, book){
    printf("%s - %s\n", jval_s(p->key), jval_s(p->val));
  };
}

void add(JRB book)
{
  char name[30], num[20];
  printf("Enter name: ");
  scanf("%s", name);
  while(getchar()!='\n');
  printf("Enter phonenumber: "); scanf("%s", num);
  JRB result = jrb_find_str(book, strdup(name));
  if(result == NULL)
    jrb_insert_str(book, strdup(name), new_jval_s(strdup(num)));
  else {
    if(strcmp(strdup(num), jval_s(result->val)) == 0)
      {
	printf("The contact exists !!!\n");
	return;
      }
    else {
      jrb_insert_str(book, strdup(name), new_jval_s(strdup(num)));
    }
  }
  printf("Succesful insertion!!!\n");
}

void searchByName(JRB book)
{
  char name[30];
  printf("Enter name: ");
  scanf("%[^\n]s", name);
  while(getchar()!='\n');
  /* JRB result = jrb_find_str(book, strdup(name)); */
  /* if(result == NULL) */
  /*   printf("That contact does not exist!!!\n"); */
  /* else { */
    
  /*   printf("Phonenumber: %s\n", jval_s(result->val)); */
  /* } */
  JRB node;
  jrb_traverse(node, book)
    {
      if(strcmp(jval_s(node->key), strdup(name)) == 0)
	{
	  printf("%s - %s\n", name, jval_s(node->val));
	}
    };
}

void searchByNumber(JRB book)
{
  char num[20];
  printf("Enter phonenumber: "); scanf("%[^\n]s", num);
  while(getchar()!='\n');
  JRB node;
  jrb_traverse(node, book){
    if(strcmp(jval_s(node->val), strdup(num)) == 0)
      {
	printf("%s - %s\n", jval_s(node->key), num);
	return;
      }
  };
  printf("There's no contact sastifying %s\n", num);
}

void delete(JRB book)
{
  char name[30];
  printf("Enter name: ");
  scanf("%[^\n]s", name);
  while(getchar()!='\n');
  JRB node = jrb_find_str(book, strdup(name));
  if(node != NULL)
    {
      jrb_delete_node(node);
      printf("Deleted successfully!\n");
    }
  else {
     printf("That contact does not exist!!!\n");
  }
}

void edit(JRB book)
{
  char name[30];
  char num[20];
  printf("Enter name: ");
  scanf("%[^\n]s", name);
  while(getchar()!='\n');
  JRB result = jrb_find_str(book, strdup(name));
  if(result == NULL)
    {
      printf("That contact does not exist!!!\n");
      return;
    }
 
  printf("Enter phonenumber: "); scanf("%[^\n]s", num);
  while(getchar()!='\n');
  if(strcmp(strdup(num), jval_s(result->val)) == 0)
    {
      printf("The same contact!!!\n");
      
    }
  else {
    jrb_delete_node(result);
    jrb_insert_str(book, strdup(name), new_jval_s(strdup(num)));
    printf("Edited !\n");
  }
  
}

void save(JRB book, char *filename)
{
  JRB node;
  FILE *f = fopen(filename, "w+");
  jrb_traverse(node, book)
    {
      fprintf(f,"%s\t%s\n", jval_s(node->key), jval_s(node->val));
    };
  fclose(f);
  printf("Saved !\n");
}


int main(int argc, char *argv[])
{
   if (argc != 2) {
        printf("Syntax: ./menu filename\n");
        return 1;
    }

   int choose=99;
   JRB book = make_jrb();
   char name[30];
   char num[20];
  
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
	  if(fscanf(f,"%*c") == EOF)
	    break;
	  fscanf(f,"%[^\n]", num); fscanf(f,"%*c");
	  
	  JRB node = jrb_insert_str(book, strdup(name), new_jval_s(strdup(num)));
	  printf("%s - %s\n", jval_s(node->key), jval_s(node->val));

	}
    }
   /* JRB node; */
   /* jrb_traverse(node, book){ */
   /*   printf("%s - %s\n", jval_s(node->key), jval_i(node->val)); */
   /* }; */
   fclose(f);
   while (choose != 0) {
     menu();
     scanf("%d", &choose);
     switch(choose) {
     case 0:
       break;
     case 1:
       print_book(book);
       break;
       
     case 2:
       while(getchar()!='\n');
       add(book);
       break;
     case 3:
       while(getchar()!='\n');
       searchByName(book);
       break;
     case 4:
       while(getchar()!='\n');
       searchByNumber(book);
       break;
     case 5:
       while(getchar()!='\n');
       delete(book);
       break;
     case 6:
       while(getchar()!='\n');
       edit(book);
       break;
     case 7:
       save(book,argv[1]);
       
       jrb_free_tree(book);
       return 0;
       break;
     default:
       
       printf("Invalid input!!!\nPlease choose ");
       break;
      }
    }
    


   jrb_free_tree(book);
   return 0;
}
