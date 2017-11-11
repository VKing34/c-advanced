#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
