#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jval.h"
#include"jrb.h"

void print_book(JRB book)
{
  JRB node;
  jrb_traverse(node, book){
    printf("%s - %li\n", jval_s(node->key), jval_l(node->val));
  };
}


void find(JRB book)
{
  char name[30];
  printf("Enter name: ");
  scanf("%s", name);
  JRB result = jrb_find_str(book, strdup(name));
  if(result == NULL)
    printf("That contact does not exist!!!\n");
  else {
    
    printf("Phonenumber: %li\n", jval_l(result->val));
  }
}




int main()
{
  JRB book = make_jrb();

  char name1[20] = "vuong";
  char *name2 = "thoa";
  char *name3 = "minhto";
  char *name4 = "thanh";
  jrb_insert_str(book, name1, new_jval_l(8495343432));
  jrb_insert_str(book, name2, new_jval_l(84162228388));
  jrb_insert_str(book, name3, new_jval_l(8490954345));
  jrb_insert_str(book, name4, new_jval_l(84165232322));

  print_book(book);
   
  find(book);
  jrb_free_tree(book);
  return 0;
  
}

/* To compile: gcc -o phone phonebook.c libfdr.a && ./phone */
