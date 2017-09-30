#include<stdio.h>
#include<stdlib.h>
#include"btree.h"

int main(int argc, char *argv[])
{
  if ( argc != 2)
    {
      printf("Warning!!!\n");
      return 1;
    }
  
  BTA *tree = btcrt("test1.txt", 0, FALSE);

  
  
}
