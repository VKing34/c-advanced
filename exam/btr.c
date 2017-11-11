#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<termio.h>
#include<unistd.h>
#include<time.h>
#include"bt/inc/btree.h"
#define max1 40
#define max2 20

void menu()
{
  printf("---------------------------------------------------------\n");
  printf("\t\t DNS \n");
  printf("---------------------------------------------------------\n");
  printf(" 1. Read and print all\n 2. Add\n 3. Search by domain\n 4. Search by IP\n 0. Quit\nChoose one option: ");
}

void print_tree(BTA *root)
{
  BTint value;
  char domain[max1], ip[max2];
  int rsize;
  btpos(root, ZSTART);
  while(bnxtky(root,domain, &value) == 0)
    {
      if(btsel(root, domain, ip, max2, &rsize) == 0)
	printf("%s : %s\n", domain, ip);
    }
}



int read_file(BTA *root, char *filename)
{
  FILE *f = fopen(filename, "r");
  if(f == NULL)
    {
      printf("File %s does not exist!!!\n", filename);
      return 0;
    }
  char domain[max1], ip[max2];
  int total;
  fscanf(f,"%d\n", &total);
  while(1)
    {
      if(feof(f))
  	break;
      if(fscanf(f,"%[^\n]\n", domain) == EOF)
	{
	  break;
	}
      fscanf(f,"%[^\n]\n", ip);
      btins(root, domain, ip, max1);
    }
  print_tree(root);
  fclose(f);
  return total;
}

char *input_string(int Max)
{
  char s = (char)malloc(Max*sizeof(char));
  scanf("%[^\n]%*c", s);
  return s;
}

int check_ip1(BTA *root, char *ip)
{
  BTint value;
  char check = (char)malloc(sizeof(char*)*max2);
  char domain = (char)malloc(sizeof(char*)*max1);
  int rsize;
  btpos(root, ZSTART);
  while(bnxtky(root, domain, &value) == 0)
    {
      if(btsel(root, domain, check, max2, &rsize) == 0)
	{
	  if(strcmp(check, ip) == 0)
	    return 1;
	}
    }
  return 0;
}

char *check_ip(BTA *root, char *ip)
{
  BTint value;
  char check = (char)malloc(sizeof(char*)*max2);
  char domain = (char)malloc(sizeof(char*)*max1);
  int rsize;
  btpos(root, ZSTART);
  while(bnxtky(root, domain, &value) == 0)
    {
      if(btsel(root, domain, check, max2, &rsize) == 0)
	{
	  if(strcmp(check, ip) == 0)
	    return domain;
	}
    }
  return NULL;
}

int check_domain(BTA *root, char *domain)
{
  int rsize;
  btpos(root, ZSTART);
  char check = (char)malloc(sizeof(char*)*max2);
  if(btsel(root, domain, check, max2, &rsize) == 0)
    return 1;
  else
    return 0;
}


int add(BTA *root)
{
  char *domain, *ip;
  int rsize;
  printf("Enter domain: "); domain = input_string(max1);
  printf("Enter IP: "); ip = input_string(max2);
  if (check_ip(root, ip) == 0)
    {
      if (check_domain(root, domain) == 0)
	{
	  btins(root, domain, ip, max1);
	  printf("Insert succesfully!\n");
	  return 1;
	}
      else {
	domain = strcat(domain,"[1]");
	 btins(root, domain, ip, max1);
	 printf("Insert succesfully!\n");
	 return 1;
      }
    }
  else {
    printf("The IP address exists!!!\n");
    return 0;
  }
}

void searchByDomain(BTA *root)
{
  printf("Enter domain: ");
  char *domain = input_string(max1);
  BTint value;
  int rsize;
  /* btpos(root, ZSTART); */
  char ip = (char)malloc(sizeof(char*)*max2);
  /* while(bnxtky(root, domain, &value) == 0) */
  /*   { */
  if(btsel(root, domain, ip, max2, &rsize) == 0)
    {
      printf("%s : %s\n",domain, ip);
    }
  if(bnxtky(root, domain, &value) == 0)
    {
      if(btsel(root, domain, ip, max2, &rsize) == 0)
	{
	  printf("%s : %s\n",domain, ip);
	}
    }
    /* } */
  
}

void searchByIP(BTA *root)
{
  printf("Enter IP: ");
  char *ip = input_string(max2);
  char domain = (char)malloc(sizeof(char*)*max1);
  domain = check_ip(root, ip);
  if(domain != NULL)
    {
      printf("%s : %s\n", domain, ip);
    }
  else {
    printf("There is no IP in the record!!!\n");
  }
}

void save(BTA *root, char *filename, int total)
{
  BTint value;
  char domain[max1], ip[max2];
  int rsize;
  btpos(root, ZSTART);
  FILE *f = fopen(filename, "w+");
  fprintf(f,"%d\n",total);
  while(bnxtky(root, domain, &value) == 0)
    {
      btsel(root, domain, ip, max2, &rsize);
      fprintf(f,"%s\n%s\n", domain, ip);
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
  int total=0, read=0;
  BTA *dns;
  btinit();
  dns = btcrt("dns_map", 0, FALSE);
  
  while(choose != 0)
    {
      menu();
      scanf("%d", &choose); 
      switch(choose)
	{
	case 0:
	  save(dns, argv[1], total);
	  break;
	case 1:
	  if(read == 0)
	    {
	      total += read_file(dns, argv[1]);
	      read =1;
	    }
	  else {
	    print_tree(dns);
	  }
	  printf("%d\n", total);
	  break;
	case 2:
	  while(getchar()!='\n');
	  if(add(dns) == 1)
	    {
	      total++;
	    }
	  save(dns, argv[1], total);
	  printf("%d\n", total);
	  break;
	case 3:
	  while(getchar()!='\n');
	  searchByDomain(dns);
	  break;
	case 4:
	  while(getchar()!='\n');
	  searchByIP(dns);
	  break;
	default:
	  printf("Invalid input!!!\nPlease try again !\n");
	  break;
	}
    }
  btcls(dns);
  total =0;
  return 0;
}

/* gcc -o btr btr.c -Lbt/lib -lbt -Ibt/inc && ./btr */
