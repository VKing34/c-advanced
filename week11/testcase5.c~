// test for huffman tree
#include <string.h>
#include "huffman.h"

int main()
{
	/*char buffer[] = "a";
	int size = strlen(buffer);
	//printf("%d\n", size);
	int bits[20];
	Coding htable[256];
	Coding htable2[256];
	HuffmanTree htree = makeHuffman(buffer, size);
	createHuffmanTable(htree, htree.root, htable, 0, bits);
	
	HuffmanTree htree2 = makeHuffman("abcabcbbb", 9);
	createHuffmanTable(htree2, htree2.root, htable2, 0, bits);
	*/
	char buffer[] = "abcabcbbb";
	int size = strlen(buffer);
	char huffman[size];
	int nbits = 0;
	int i;

	compress(buffer, size, huffman, &nbits);

	printf("The size after compressed is %d bits\n", nbits);
	for(i = 0; i < nbits; i++){
		printf("%d", getBit(huffman[i/7], i%7));
	}

	printf("\n");
}