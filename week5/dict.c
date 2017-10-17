#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<termio.h>
#include<unistd.h>
#include<time.h>
#include"bt/inc/btree.h"
#include"soundex.h"
#include"autocp.h"
#define Max 50

void menu()
{
  printf("---------------------------------------------------------\n");
  printf("\t\t Dictionary\n");
  printf("---------------------------------------------------------\n");
  printf(" 1. Look up words\n 2. Add a word with meaning\n 3. Remove a existing word\n 4. Quit with saving\n 0. Quit\nChoose one option: ");
}


int addWord(BTA *root,char *word, char *meaning)
{
  char *check = (char*)malloc(sizeof(char) * Max);
  int rsize;
  if(btsel(root,word, check, Max, &rsize) == 0)
    {
      if(strcmp(check,meaning) != 0)
	{
	  printf("Do you want to replace the meaning of %s?(y/Y or n/N)", word);
	  char answer = getchar();
	  if(answer == 'y' || answer == 'Y')
	    btupd(root,word,meaning,Max);
	}
      return 1;
    }
  else {
    btins(root, word, meaning, Max);
    return 0;
  }
}

int addSoundex(BTA *root, char *word)
{
  char s[10];
  int rsize;
  soundEx(s,word, Max, 1);
  btins(root, s, word, Max);
  return 0;
}


int readFile(BTA *dict, BTA *sdex, char *filename)
{
  FILE *f = fopen(filename, "r");
  if(f == NULL)
    {
      printf("File %s does not exist!!!\n", filename);
      return 1;
    }
  char word[Max], meaning[Max];
  while(1)
    {
      if(feof(f))
  	break;
      if(fscanf(f,"%[^\t]", word) == EOF)
  	break;
      if(fscanf(f,"%*c") == EOF)
  	break;
      fscanf(f,"%[^\n]\n", meaning);

      if(addWord(dict, word, meaning) == 0)
      	{
      	  addSoundex(sdex,word);
      	}
    
    }
  /* char a; */
  /* while(1) */
  /*   { */
  /*     if(feof(f)) */
  /* 	break; */
  /*     fscanf(f,"%[^@]"); */
  /*     fscanf(f,"%*c",a); */
  /*     if(fscanf(f,"%[^\n/]",word) == EOF) */
  /* 	break; */
	
  /*     fscanf(f,"%[^-]"); */
  /*     fscanf(f,"%*c"); */
  /*     fscanf(f,"%[^\n]",meaning); */
  /*     if(addWord(dict, word, meaning) == 0) */
  /* 	{ */
  /* 	  addSoundex(sdex,word); */
  /* 	} */
  /*     printf("%s - %s\n", word, meaning); */
  /*   } */
  fclose(f);
  return 0;
}


void print_tree(BTA *root)
{
  BTint value;
  char word[50], meaning[50];
  int rsize;
  btpos(root, ZSTART);
  while(bnxtky(root,word, &value) == 0)
    {
      if(btsel(root, word, meaning, 50, &rsize) == 0)
	printf("%s : %s\n", word, meaning);
    }
}

void print_word(char *word, char *meaning)
{
  printf("%s : %s\n", word, meaning);
}

void save(BTA *root, char *filename)
{
  BTint value;
  char word[Max], meaning[Max];
  int rsize;
  btpos(root, ZSTART);
  FILE *f = fopen(filename, "w+");
  while(bnxtky(root, word, &value) == 0)
    {
      btsel(root, word, meaning, 50, &rsize);
      fprintf(f,"%s\t%s\n", word, meaning);
    }
  fclose(f);
}

char *search_mean(BTA *root, char *word)
{
  int rsize;
  char *meaning= (char*)malloc(sizeof(char) * 50);
  btpos(root, ZSTART);
  if(btsel(root, word, meaning, 50, &rsize) == 0)
    {
      return meaning;
    }
  else {
    return NULL;
  }
}

void lookup(BTA *dict, BTA *sdex)
{
  char input[]="Enter word to look up: ";
  char *word = (char*)malloc(sizeof(char)*Max);
  write(STDOUT_FILENO,input, strlen(input));
  tab_complt(dict, word);
  char *meaning;
  meaning = search_mean(dict, word);
  if(meaning == NULL)
    {
      printf("%s is not in the dictionary !\n", word);
    }
  else {
    print_word(word, meaning);
  }
}

char *input_string()
{
  char *s = (char*)malloc(Max*sizeof(char));
  scanf("%[^\n]%*c", s);
  return s;
}

void insertWord(BTA *dict, BTA *sdex)
{
  char *word, *meaning;
  char *check;
  int rsize;
  printf("Enter word: "); word = input_string();
  printf("Enter meaning: "); meaning = input_string();
  if(addWord(dict, word, meaning) == 0)
    {
      addSoundex(sdex,word);
      printf("Successful Insertion!\n");
    }
 
}

void delWord(BTA *dict, BTA *sdex)
{
  int rsize;
  char input[]="Enter word to delete: ";
  char *word = (char*)malloc(sizeof(char)*Max);
  write(STDOUT_FILENO,input, strlen(input));
  tab_complt(dict, word);
  if(btdel(dict, word) != 0)
    {
      printf("%s is not in the dictionary!!!\n", word);
    }
  else {
    char s[10];
    soundEx(s,word,Max,1);
    btdel(sdex,s);
    printf("Delete successfully!!\n");
  }
  free(word);
}

int main(int argc,char *argv[])
{
  if(argc != 2)
    {
      printf("Wrong syntax!!!\nSyntax: ./%s <filename>\n",argv[0]);
      return 1;
    }

  int choose=9;
  BTA *dict;
  BTA *sdex;
  btinit();
  dict = btcrt("map_words", 0, FALSE);
  sdex = btcrt("map_soundex", 0, FALSE);
  if(readFile(dict, sdex, argv[1]) != 0)
    return 1;
  print_tree(dict);
  print_tree(sdex);
  while(choose != 0)
    {
      menu();
      scanf("%d", &choose); 
      switch(choose)
	{
	case 0:
	  break;
	case 1:
	  while(getchar()!='\n');
	  lookup(dict, sdex);
	  break;
	case 2:
	  while(getchar()!='\n');
	  insertWord(dict,sdex);
	  break;
	case 3:
	  while(getchar()!='\n');
	  delWord(dict,sdex);
	  /* print_tree(dict); */
	  /* print_tree(sdex); */
	  break;
	case 4:
	  save(dict,argv[1]);
	  goto ending;
	default:
	  printf("Invalid input!!!\nPlease try again !\n");
	  break;
	}
    }
  
 ending:
  btcls(dict);
  btcls(sdex);
  
  return 0;
}
