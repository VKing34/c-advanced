#include <string.h>
#include <stdio.h>
#include"dirgraph.h"

void menu()
{
	printf("---------------------------------------------------------\n");
  	printf("\t\t MENU \n");
  	printf("---------------------------------------------------------\n");
  	printf(" 1. \n 2. \n 3. \n 4. \n 5. \n 6. \n 7. Quit\nChoose one option: ");
}


int main()
{
	int choose;

	Graph g = createGraph();
	while(choose != 7)
	{
		menu();
		scanf("%d", &choose);
		switch(choose)
		{
			case 1:
			
			break;

			case 2:
			while(getchar()!='\n');

			break;

			case 3:
			break;
			case 4:
		
			break;

			case 5:
			break;

			case 6:
			
			break;

			case 7:
			break;

			default:
			printf("Invalid input!!!\n");
			break;
		}
	}

	dropGraph(g);
	return 0;
}

// gcc -g -o exam exam.c dirgraph.c libfdr.a && ./exam