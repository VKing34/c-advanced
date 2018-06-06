#include<stdio.h>
#include<stdlib.h>

int partition(int *list, int first, int last)
{
	int pivot = list[first];
	int leftmark = first+1, rightmark = last;

	while(1)
	{
		while(list[leftmark] <= list[rightmark] && list[leftmark] <= pivot)
			leftmark++;
		while(list[rightmark] >= list[leftmark] && list[rightmark] >= pivot)
			rightmark--;
		if(leftmark > rightmark)
			break;
		else {
			int temp = list[leftmark];
			list[leftmark] = list[rightmark];
			list[rightmark] = temp;
		}
	}
	int temp = pivot;
	list[first] = list[rightmark];
	list[rightmark] = pivot;
	return rightmark;
}

void quickSort(int *list, int first, int last)
{
	if(first < last)
	{
		int splitPoint = partition(list, first, last);
		quickSort(list,first, splitPoint);
		quickSort(list,splitPoint+1, last);
	}
}
 
void main()
{
	int list[5] = {23,1,12,65,22};
	int i;
	for(i = 0; i<5; i++)
	{
		printf("%d \t",list[i]);
	}
	printf("\n");
	quickSort(list,0,4);
	for(i = 0; i<5; i++)
	{
		printf("%d \t",list[i]);
	}
	printf("\n");
}
