#include"huffman.h"


JRB countFreq(char *buffer, int size)
{
  JRB freqTree, node;
  int i, val;

  freqTree = make_jrb();

  for(i = 0; i< size; i++)
    {
      node = jrb_find_int(freqTree, buffer[i]);
      if(node)
	{
	  val = jval_i(node->val)+1;
	  node->val = new_jval_i(val);
	}
      else {
	jrb_insert_int(freqTree, buffer[i], new_jval_i(1));
      }
    }
  /* jrb_traverse(node, freqTree) */
  /*   { */
  /*     printf("%c : %d\n", jval_i(node->key), jval_i(node->val)); */
  /*   } */

  return freqTree;
}


JRB makePQueue(JRB freqTree)
{
  JRB Queue = make_jrb();
  JRB node;
  jrb_traverse(node, freqTree)
    {
      jrb_insert_int(Queue, jval_i(node->val), node->key);
    }
  /* jrb_traverse(node, Queue) */
  /*   { */
  /*     printf("%d : %c\n", jval_i(node->key), jval_i(node->val)); */
  /*   } */
  return Queue;
}

JRB dequeue_pq(JRB pqueue, JRB *cur, int n)
{
  JRB p;
  if(n == 0)
    {
      n++;
      *cur = jrb_first(pqueue);
      return *cur;
    }
  else {
    p = *cur;
    *cur = jrb_next(p);
    if(p == NULL)
      {
	return NULL;
      }
    return *cur;
  }
}


huffmanTree makeHuffman(char *buffer, int size)
{
  if(buffer == NULL)
    {
      printf("ERROR: Input is null!!!Please check it again\n");
      exit(1);
    }
  
  JRB freqTree = countFreq(buffer, size);
  JRB pqueue = makePQueue(freqTree);
  JRB queue_pointer = jrb_first(pqueue);
  JRB node1, node2;
  int n = -1;
  int parent, c1, c2, f1, f2;
  

  huffmanTree hmTree = {createGraph(), 0};   // huffmanTree{Graph g = createGraph(); int root =0}


  if(size == 1)
    {
      hmTree.root = buffer[0];
      hmTree.g.edges = NULL;
      hmTree.g.vertices = NULL;
      return hmTree;
    }

   Graph g = hmTree.g;

   while(queue_pointer != jrb_nil(pqueue))
     {
       n++;
       node1 = dequeue_pq(pqueue, &queue_pointer, n);
       n++;
       node2 = dequeue_pq(pqueue, &queue_pointer, n);

       if(node1 != jrb_nil(pqueue) && node2 != jrb_nil(pqueue))
	 {
	   c1 = jval_i(node1->val);
	   c2 = jval_i(node2->val);
	   f1 = jval_i(node1->key);
	   f2 = jval_i(node2->key);

	   parent = c1 + c2;
	  
	   addEdge(g, parent, c1, 0);
	   addEdge(g, parent, c2, 1);
	   addVertex(g, parent, NULL);
	   addVertex(g, c1, NULL);
	   addVertex(g, c2, NULL);
	   
	   jrb_insert_int(pqueue, f1+f2, new_jval_i(parent));
	 }
     }
   /* jrb_traverse(node1, g.vertices) */
   /*   { */
   /*     printf("%d\n", jval_i(node1->key)); */
   /*   } */
   
   //jrb_traverse(node2, g.edges)
   //  {
   //    printf("%d\n", jval_i(node2->key));
    // }

   /* jrb_traverse(node1, pqueue) */
   /*   { */
   /*     printf("$d\n", jval_i(node1->key)); */
   /*   } */
   
   hmTree.root = parent;

   return hmTree;
}

void addHuffmanChar(int ch, coding *hmTable, int *bits, int n)
{
  int i;
  int code = 0;
  hmTable[ch].size = n;
  printf("%c: ", ch);

  for(i =0; i<n ; i++)
    {
      printf("%d", bits[i]);
      code = code | (bits[i] << i);
    }
  printf("\n");
  hmTable[ch].bits = code;
}

void createHuffmanTable(huffmanTree hmTree, int root, coding *hmTable, int level, int *bits)
{
  int adjVertices[2];
  int i;

  if(!hmTree.g.edges && !hmTree.g.vertices)
    {
      hmTable[hmTree.root].size = 1;
      hmTable[hmTree.root].bits = 0;
      return;
    }
  
  int n = getAdjVertices(hmTree.g, root, adjVertices);
 // printf("%d\n", root);
 // printf("%d\n", n);

  if(n == -1)
    {
      addHuffmanChar(root, hmTable, bits, level);
      return;
    }

  for(i=0; i<2; i++)
    {
      bits[level] = (int) getWeight(hmTree.g, root, adjVertices[i]);
      createHuffmanTable(hmTree, adjVertices[i], hmTable, level+1, bits);
    }
 
}

int getBit(int bits, int offset)
{
  int test = 1 << offset;
  int result = bits & test;
  if(result)
    {
      return 1;
    }
  else {
    return 0;
  }
}

void encode(char ch, coding *hmTable, char *huffman, int *nbit)
{
  int length = hmTable[ch].size;
  int pos = *nbit;
  int i, e, offset, bit;

  for(i=0; i<length; i++)
    {
      e = (pos + i) / 7;
      offset = (pos + i) % 7;
      bit = getBit(hmTable[ch].bits, i);
      if(bit)
	{
	  huffman[e] = huffman[e] | (bit << offset);
	  /* printf("%d\n", bit); */
	}
    }
  *nbit += length;
}

void compress(char *buffer, int size, char *huffman, int *nbit)
{
  huffmanTree hmTree = makeHuffman(buffer, size);
  coding hmTable[256];
  int bits[100];
  int i;
  *nbit = 0;
        
  createHuffmanTable(hmTree, hmTree.root, hmTable, 0, bits);

  for(i=0; i<size;i++)
    {
      huffman[i]=0;
    }
  for(i=0; i<size; i++)
    {
      encode(buffer[i], hmTable, huffman, nbit);
    }
}


