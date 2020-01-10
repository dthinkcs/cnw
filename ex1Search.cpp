#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lSearch(int key, int size, int* a)
{
	for (int i = 0; i < size; i++)
	{
		if (a[i] == key)
			return i;
	}
	return -1;
}

int bSearch(int key, int size, int *a)
{
	int start = 0, end = size - 1;
	int mid;
	while (1 && start <= end)
	{
		mid = (start + end) / 2;
		if (*(a + mid) == key)
			return mid;
		if (start == end)
			return -1;
		if (key < *(a + mid))
			end = end - 1;
		else if (key > *(a + mid))
			start = start + 1;
	}
	return -1;
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
	int key;
	printf("Enter ele to searched:");
	scanf("%d", &key);
	int ans = lSearch(key, size, a);
	printf("LSearch result:%d\n", ans);
	ans = bSearch(key, size, a);
	printf("BSearch result:%d\n", ans);

}
