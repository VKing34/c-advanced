#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define max 1000000

void createArray(int a[], int size, int MAX)
{
  int i;
  srand(time(NULL));
  for (i=0;i<size;i++)
    {
      a[i]= rand() % MAX+1;
    }
}

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void sort(int a[],int left, int right)
{
  if(right <= left) return;
  int lt = left, gt = right;
  int pivot = a[left];
  int i = left;
  while(i <= gt)
    {
      if(a[i] == pivot)
	++i;
      else if(a[i] > pivot)
	swap(&a[i], &a[gt--]);
      else
	{
	  swap(&a[i++], &a[lt++]);
	}
	 
    }
  sort(a,left, lt-1);
  sort(a, gt+1, right);
}

int main()
{
  int a[max];
  int i, j=1;
  createArray(a,max,10);
  for(i=0; i<max; i++)
    {
      if (j==5)
	{
	  printf("\n");
	  j=1;
	}
      printf("%d\t",a[i]);
      j++;
     
    }
  printf("\n");
  printf("After:\n");
  sort(a,0,max-1);
  j=1;
   for(i=0; i<max; i++)
    {
      if (j==5)
	{
	  printf("\n");
	  j=1;
	}
      printf("%d\t",a[i]);
      j++;
     
    }
   printf("\n");
  return 0;
  
}
