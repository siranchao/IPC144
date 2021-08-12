#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define SZ 3

int main(void)
{
	int key[SZ] = { 234, 567, 948 };
	int value[SZ] = { 0 };
	int i;

	for ( i = 0; i < SZ; i++)
	{
		printf("Please enter a value for key %d: ", key[i]);//user enters 7, then 6, then 9
		scanf("%d", &value[i]);
	}
	printf("\n\n");

	for ( i = 0; i < SZ; i++)
	{
		if (value[i] % 2)
		{
			value[i]++;
		}
		printf("The value of key: %d is %d\n", key[i], value[i]);
	}

	return 0;
}