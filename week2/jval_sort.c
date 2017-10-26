#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 5

#include"jval.h"

int string_compare(Jval *a, Jval *b)
{
  return strcmp(a->s, b->s);
}

int int_compare(Jval *a, Jval *b)
{
  return a->i - b->i;
}

void swap(Jval *a, Jval *b)
{
  Jval temp = *a;
  *a = *b;
  *b = temp;
  
}

void jval_sort(Jval *a, int left, int right, int (*compare)(Jval*, Jval*))
{
  if(left >= right)
    return;
  int lt = left, gt = right;
  Jval *pivot = &a[left];
  int i = left;
  while(i <= gt)
    {
      if(compare(pivot, &a[i]) == 0)
	++i;
      else if(compare(pivot, &a[i]) < 0)
	{
	  swap(&a[i], &a[gt--]);
	}
      else {
	swap(&a[i++], &a[lt++]);
      }
    }
  jval_sort(a, left, lt-1, compare);
  jval_sort(a, gt+1, right, compare);
}


int main()
{
  Jval a[max];
  a[0].i = 3;
  a[1].i = 2;
  a[2].i = 7;
  a[3].i = 1;
  a[4].i = 5;

  jval_sort(a, 0, 4, int_compare);
  for(int i=0; i<5; i++)
    {
      printf("%d\n", a[i].i);
    }

  Jval b[4];
  b[0] = new_jval_s("Anh");
  b[1] = new_jval_s("Yeu");
  b[2] = new_jval_s("Em");
  b[3] = new_jval_s("Lam");

  
  jval_sort(b, 0, 3, string_compare);
  for(int j=0; j<4; j++)
    {
      printf("%s\n", b[j].s);
    }
  return 0;
}
