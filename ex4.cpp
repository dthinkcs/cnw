#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int size;
	scanf("%d", &size);
	FILE *fptr;
	fptr = fopen("write.txt", "w");
	for (int i = 0; i < size; i++)
	{
		fprintf(fptr, "%d", i);
		fprintf(fptr, "%s", "\n");
	}
	fclose(fptr);
	int num;
	fptr = fopen("write.txt", "r");
	for (int i = 0; i < size; i++)
	{
		fscanf(fptr, "%d", &num);
		printf(">>%d", num);
	}
	fclose(fptr);

	return (0);
}
