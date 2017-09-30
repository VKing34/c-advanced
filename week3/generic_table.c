#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INITIAL_SIZE 3
#define INCREMENTAL_SIZE 2

typedef struct {
  void *key;
  void *value;

}Entry;

typedef struct {
  Entry *entries;
  int size, total;
  Entry (*makeNode)(void*, void*);
  int (*compare)(void*, void*);
}SymbolTable;

Entry makePhone(void *name, void* number)
{
  Entry phone;
  phone.key = strdup((char*)name);
  phone.value = malloc(sizeof(long));
  memcpy(phone.value, number,sizeof(long));

  return phone;
}

int comparePhone(void *key1, void *key2)
{
  return strcmp((char*)key1, (char*)key2);
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*), int (*compare)(void*, void*))
{
  SymbolTable tab;
  tab.entries = (Entry*)malloc(sizeof(Entry) * INITIAL_SIZE);
  tab.size = INITIAL_SIZE;
  tab.total = 0;
  tab.makeNode = makeNode;
  tab.compare = compare;
  return tab;
}
void dropSymbolTable(SymbolTable tab)
{
  if(tab.total == 0)
    return;
  for(int i =0; i < tab.total; i++)
    {
      free(&(tab.entries[i]));
    }
  tab.total=0;
  tab.size = INITIAL_SIZE;
}

void addEntry(void *key, void *value, SymbolTable *tab)
{
  if(tab->total == 0)
    {
      tab->entries[0] = tab->makeNode(key, value);
      tab->total++;
     
      return;
    }
  int i;
  for(i=0; i < tab->total; i++)
    {
      if( tab->compare(key, tab->entries[i].key) == 0)
	{
	  printf("The key exists!\n");
	  return;
	}
    }
  if(tab->total == tab->size +1)
    {
      tab->size += INCREMENTAL_SIZE;
      tab->entries = (Entry*)realloc(tab->entries, tab->size*sizeof(Entry));
    }

  tab->entries[tab->total++] = tab->makeNode(key, value);
}

/* Entry *getEntry(void* key, SymbolTable tab) */
/* { */
/*   if(tab.total == 0) */
/*     { */
/*       return NULL; */
/*     } */
/*   for(int i = 0; i < tab.total; i++) */
/*     { */
/*       if(tab.compare(key, tab.entries[i].key) == 0) */
/* 	return &(tab.entries[i]); */
/*     } */
/*   return NULL; */
/* } */

Entry *getEntry(void *key, SymbolTable *tab)
{
  if(tab->total == 0)
    {
      return NULL;
    }
  Entry *res = tab->entries;
  for(int i = 0; i < tab->total; i++)
    {
      if(tab->compare(key, res->key) == 0)
	return res;
      res++;
    }
  return NULL;
}

void print(SymbolTable tab)
{
  if(tab.total == 0)
    {
      printf("There's no entries\n");
      return;
    }
  for(int i = 0; i< tab.total; i++)
    {
      printf("%s - %li\n", tab.entries[i].key, (*(long*)(tab.entries[i].value)));
    }
}

int main()
{
  SymbolTable book = createSymbolTable(makePhone, comparePhone);
  
  long p1 = 8496564453;
  long p2 = 84162343235;
  long p3 = 84165342342;
  long p4 = 8490232111;
  addEntry("vuong", &p1, &book);
  addEntry("tu", &p2, &book);
  addEntry("thanh", &p3, &book);
  print(book);
  printf("-------------------------\n");
  addEntry("thoa", &p4, &book);
  print(book);
  printf("-------------------------\n");
  printf("thanh has phonenumber: %li\n", *(long*)getEntry("thanh",&book)->value );
  printf("-------------------------\n");
  return 0;
}
