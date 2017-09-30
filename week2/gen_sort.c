#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int int_compare(void *a, void *b)
{
  return *(int*)a - *(int*)b;
}


int str_compare(void *a, void *b)
{
  return strcmp(a,b);
}

int str_compare_v2( void *a,  void *b)
{
 
  return strcmp( &(*(char*)a), &(*(char*)b));
}

  
void swap(void* key1, void* key2, size_t width)
{
  unsigned char *tmp = malloc(width);
  memcpy(tmp, key1, width);
  memcpy(key1, key2, width);
  memcpy(key2, tmp, width);
}

void gen_qsort(void *a, int left, int right, size_t width, int (*compare)(void*, void*))
{
  if(right <= left)
    return;
  int lt = left, gt = right;
  void *pivot = a + left*width;
  int i = left;
  while(i <= gt)
    {
      if(compare(pivot, a + i*width) == 0)
	++i;
      else if(compare(pivot, a + i*width) < 0)
	{
	  swap(a + i*width, a + gt*width, width);
	  --gt;
	}
      else {
	swap(a + i*width, a + lt*width, width);
	++i;
	++lt;
      }
    }
  gen_qsort(a, left, lt-1, width, compare);
  gen_qsort(a, gt+1, right, width, compare);
}

int main(){
  int a[] = {1, 3, 4, 52, 2, 3};
  char a2[5][20] = { "jhsa", "asndb", "drtfe", "nhurh", "bvhr"};
  char *a3[] = { "jhsa", "asndb", "drtfe", "nhurh", "bvhr"}; 
  int i = 0;
  gen_qsort(a, 0, 5, sizeof(int), int_compare);    
  for(i = 0; i < 6; i++){
    printf("\n%d", a[i]);
  }
  gen_qsort(a2, 0, 4, sizeof(*a2), str_compare);    
  for(i = 0; i < 5; i++){
    printf("\n%s", a2[i]);
  }
  printf("\n\nsort array of strings:\n\n");
  gen_qsort(a3, 0, 4, sizeof(*a3), str_compare_v2);    
  for(i = 0; i < 5; i++){
    printf("%s\n", a3[i]);
  }
  return 0; 
}
