#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
#include"jval.h"

void menu()
{
  printf("---------------------------------------------------------\n");
  printf("\t\t           \n");
  printf("---------------------------------------------------------\n");
  printf(" 1. \n 2. \n 3. \n 0. Quit\nChoose one option: ");
}

int main()
{

  int choose=9;
  
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

	  break;
	case 2:

	  break;
	case 3:

	  break;
	default:
	  printf("Invalid input!!!\nPlease try again !\n");
	  break;
	}
    }
    return 0;
}

/* gcc -o rb rb.c libfdr.a && ./rb */
