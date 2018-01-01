#include"huffman.h"

int main()
{
  char buffer[] = "abdfvxcsadqwedvejyunh";
  int size = strlen(buffer);
  char huffman[size];
  int nbit = 0;
  int i;

  compress(buffer, size, huffman, &nbit);

  printf("The size after compressed is %d bits\n", nbit);
  for(i=0;i < nbit; i++)
    {
      printf("%d", getBit(huffman[i/7], i%7));
    }
  printf("\n");
}

/* gcc -o hmtest hmtest.c dirgraph.c huffman.c libfdr.a && ./hmtest */
