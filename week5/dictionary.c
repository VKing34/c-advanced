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

typedef char str[Max];

typedef struct{
  str list[10];
  int count;
} mean;

typedef struct{
  str word[1000];
  int count;
} soundex;

void menu()
{
  printf("---------------------------------------------------------\n");
  printf("\t\t Dictionary\n");
  printf("---------------------------------------------------------\n");
  printf(" 1. Look up words\n 2. Add a word with meaning\n 3. Remove a existing word\n 4. Quit with saving\n 0. Quit\nChoose one option: ");
}

int addWord(BTA *root, char *word, char *meaning)
{
  mean *data;
  
  int rsize,i, k;
  data = (mean*)malloc(sizeof(mean));
  
  if(btsel(root,word, (char*)data, sizeof(mean), &rsize) == 0)
    {
      for(i=0; i<data->count; i++)
	if(strcmp(data->list[i],meaning) == 0)
	  k=1;
      if(k==1)
	return 0;
     else {
       strcpy(data->list[data->count], meaning);
       data->count++;
       btupd(root,word,(char*)data, sizeof(mean));
     }
    }

  else
    {
      strcpy(data->list[0],meaning);
      data->count=1;
      btins(root,word,(char*)data,sizeof(mean));
    }
  free(data);
  return 1;
}


int addSoundex(BTA *root, char *word)
{
  soundex *sd;
  char s[10];
  int rsize,i,k;
  sd = (soundex*)malloc(sizeof(soundex));
  soundEx(s,word, 50,1);
  if(btsel(root,s, (char*)sd, sizeof(soundex), &rsize) == 0)
    {
      for(i=0; i<sd->count; i++)
	if(strcmp(sd->word[i], word) == 0)
	  k =1;
      if(k==1)
	return 0;
      else {
	strcpy(sd->word[sd->count], word);
	sd->count++;
	btupd(root, s, (char*)sd, sizeof(soundex));
      }
    }
  else {
    strcpy(sd->word[0],word);
    sd->count=1;
    btins(root,s,(char*)sd, sizeof(soundex));
    
  }
  free(sd);
  return 1;
  
}

int add(BTA *dict, BTA *sdex, char *word, char *meaning)
{
  addSoundex(sdex,word);
  if(addWord(dict,word,meaning) == 1)
    {
      return 1;
    }
  else
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
      
      add(dict,sdex,word,meaning);
    }
  fclose(f);
  return 0;
}

void print_word(char *word, char *meaning)
{
  printf("%s : %s\n", word, meaning);
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

soundex *search_soundex(BTA *root, char *word)
{
  soundex *sd;
  int rsize, i;
  char s[10];
  soundEx(s,word,50,1);
  sd = (soundex*)malloc(sizeof(soundex));
  if(btsel(root,s,(char*)sd, sizeof(soundex), &rsize) == 0)
    return sd;
  else {
    free(sd);
    return NULL;
      
  }
    
}

/* void soundex_search(BTA *dict, BTA *sdex, char *word) */
/* { */
  
/* } */

void lookup(BTA *dict, BTA *sdex)
{
  char word[Max], input[]="Enter word to look up: ";
  char *word1 = (char*)malloc(sizeof(char)*Max);
  write(STDOUT_FILENO,input, strlen(input));
  tab_complt(dict, word);
  strcpy(word1, word);
  char *meaning;
  meaning = search_mean(dict,word1);
  if( meaning == NULL)
    {
     
      printf("%s is not in the dictionary !\n", word1);
      /* printf("Do you want to see words whose spell is similar to %s ?\n", word1); */
      /* answer = getchar(); */
      /* if(answer == 'y' || answer == 'Y') */
      /* 	soundex_search(dict,sdex,word1); */
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
  printf("Enter word: "); word = input_string();
  printf("Enter meaning: "); meaning = input_string();
  if(add(dict, sdex, word, meaning) == 0)
    printf("%s with meaning exists !!!\n" );
  else {
    printf("Successful insertion!\n");
  }
}



void delWord(BTA *dict, BTA *sdex)
{
  int rsize;
  soundex *s;
  char *word;
  printf("Enter word to delete: ");
  word = input_string();
  if(btdel(dict,word) != 0)
    {
      printf("%s is not in the dictionary!!!\n");

    }
  else {
    s = search_soundex(sdex, word);
    int i=0,j;
    char sd[10];
    soundEx(sd, word,50, 1);
    while(i < s->count)
      {
	if(strcmp(s->word[i], word) == 0)
	  break;
	else {
	  i++;
	}
	for(j=i;j <s->count; j++)
	  strcpy(s->word[j], s->word[j+1]);
	s->count--;
	btupd(sdex,sd,(char*)s, sizeof(soundex));
	free(s);
	printf("Delete successfully!\n" );
      }
    
  }
  free(word);
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
