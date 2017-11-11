#include"jqsort.h"

#define max 5


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
	  
  /* Jval a[max]; */
  /* a[0].i = 3; */
  /* a[1].i = 2; */
  /* a[2].i = 7; */
  /* a[3].i = 1; */
  /* a[4].i = 5; */

  /* jval_sort(a, 0, 4, int_compare); */
  /* for(int i=0; i<5; i++) */
  /*   { */
  /*     printf("%d\n", a[i].i); */
  /*   } */

  /* Jval b[4]; */
  /* b[0] = new_jval_s("anh"); */
  /* b[1] = new_jval_s("Yeu"); */
  /* b[2] = new_jval_s("Em"); */
  /* b[3] = new_jval_s("Lam"); */

  
  /* jval_sort(b, 0, 3, string_compare); */
  /* for(int j=0; j<4; j++) */
  /*   { */
  /*     printf("%s\n", b[j].s); */
  /*   } */

  return 0;
}


/* gcc -o sort sort.c libfdr.a && ./sort */
