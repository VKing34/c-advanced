#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INITIAL_SIZE 3
#define INCREMENTAL_SIZE 2

typedef struct{
  char name[30];
  long number;
} phoneEntry;

typedef struct {
  phoneEntry *entries;
  int total;
  int size;
} phoneBook;

phoneBook createPhoneBook()
{
  phoneBook book;
  book.entries = (phoneEntry*)malloc(sizeof(phoneEntry)*INITIAL_SIZE);
  book.size = INITIAL_SIZE;
  book.total = 0;
  return book;
  
}

void dropPhoneBook(phoneBook *book)
{
  book->entries == NULL;
  book->total = 0;
  book->size = 0;
}

phoneEntry makeNode(char *name, long number)
{
  phoneEntry node;
  strcpy(node.name,name);
  node.number = number;
  return node;
}

void addPhoneNumber(char *name, long number, phoneBook *book)
{

  if (book->total == 0)
    {
      book->entries[0] = makeNode(name, number);
      book->total ++;
      return;
    }
  int i;
  for(i = 0; i< book->total; i++)
    {
      if(strcmp(name, book->entries[i].name) == 0)
	{
	 
	  return;
	}
    }
  if( book->size == book->total + 1)
    {
      book->size += INCREMENTAL_SIZE;
      book->entries = (phoneEntry*)realloc(book->entries, book->size*sizeof(phoneEntry));
      
    }

  book->entries[book->total++] = makeNode(name,number);
}

phoneEntry *getPhoneNumber(char *name, phoneBook book)
{
  if(book.total == 0)
    {
      return NULL;
    }
  for(int i =0 ; i< book.total ; i++)
    {
      if(strcmp(name, book.entries[i].name) == 0)
	{
	  return &(book.entries[i]);
	}
    }
  return NULL;
}

void print(phoneBook book)
{
  if(book.total == 0)
    {
      printf("There's no entries\n");
      return;
    }
  for(int i = 0; i< book.total; i++)
    {
      printf("%s - %ld\n",book.entries[i].name, book.entries[i].number);
    }
}

int main()
{
  phoneBook book = createPhoneBook();
  
  addPhoneNumber("vuong", 9342323, &book);
  addPhoneNumber("tuoccho", 23421423, &book);
  addPhoneNumber("thanh", 34234322, &book);
  print(book);
  addPhoneNumber("thoanguxi", 16754452, &book);
  print(book);
  printf("%d\n",getPhoneNumber("thanh",book)->number );
  dropPhoneBook(&book);
  print(book);
  return 0;
}
