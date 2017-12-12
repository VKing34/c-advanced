#include"dirgraph.h"
#include<string.h>

typedef struct{
Graph g;
int root;
} huffmanTree;

typedef struct{
int size;
int bits;
} coding;

typedef struct{
int size;
int *node;
} huffmanTreeArray;

huffmanTree makeHuffman(char *buffer, int size);
void addHuffmanChar(int ch, coding *hmTable, int *bits, int n);
void createHuffmanTable(huffmanTree hmTree, int root, coding *hmTable, int level, int *bits);
int getBit(int bits, int offset);
void compress(char *buffer, int size, char *huffman, int *nbit);

