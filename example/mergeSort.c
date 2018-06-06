#include<stdio.h>
#include<stdlib.h>
#define max 20
void merge(int *list, int first, int mid, int last)
{
	int temp[max];
	int first1 = first, last1 = mid;
	int first2 = mid+1, last2 = last, index = first1;
	while ( first1 <= last1 && first2 <= last2)
	{
		if(list[first1] < list[first2])
		{
			temp[index] = list[first1];
			first1++;
			
		}
		else{
			temp[index] = list[first2];
			first2++;
		} 
			
		index++;
	}
	while(first1 <= last1)
	{
		temp[index] = list[first1];
		first1++;
		index++;
	}
	while(first2 <= last2)
	{
		temp[index] = list[first2];
		first2++;
		index++;
	}
	for(index = first; index <= last; index++)
	{
		list[index] = temp[index];
	}
	
}

void mergeSort(int *list, int first, int last)
{
	if (first < last)
	{
		int mid = (first+last)/2;
		mergeSort(list,first,mid);
		mergeSort(list,mid+1,last);

		merge(list,first,mid,last);
	}
}

void main()
{
	int list[5] = {23,43,12,65,22};
	int i;
	for(i = 0; i<5; i++)
	{
		printf("%d \t",list[i]);
	}
	printf("\n");
	mergeSort(list,0,4);
	for(i = 0; i<5; i++)
	{
		printf("%d \t",list[i]);
	}
	printf("\n");
}
