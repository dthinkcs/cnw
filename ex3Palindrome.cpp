#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int isPalindrome(int size, int *a)
{
	for (int i = 0; i <= size / 2; i++)
	{
		if (*(a + i) != *(a + size - 1 - i))
			return -1;
	}
	return 1;
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
	int ans = isPalindrome(size, a);
	printf("Palindrome: %d\n", ans);

	return (0);
}
