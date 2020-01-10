#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void bubbleSort(int size, int *a)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i; j++)
		{
			if (*(a + j) > *(a + j + 1))
			{
				int temp = *(a + j);
				*(a + j) = *(a + j + 1);
				*(a + j + 1) = temp;
			}
		}
	}
}

int main()
{
	int size;
	scanf("%d", &size);
	int *a = (int *)calloc(size, sizeof(int));
	for (int i = 0; i < size; i++)
	{
		scanf("%d", a + i);
	}
	bubbleSort(size, a);
	for (int i = 0; i < size; i++)
	{
		printf("%d\n", *(a + i));
	}

	return (0);
}
