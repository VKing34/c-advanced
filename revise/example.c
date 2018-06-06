#include<stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char s[4] = "An2";
	char c[3];
	int n;
	sscanf(s, "%*[^0123456789]%d", &n);
	printf("%d\n", n);
	return 0;
}