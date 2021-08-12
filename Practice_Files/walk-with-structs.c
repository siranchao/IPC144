#include<stdio.h>

struct PlusOrMinus
{
	int plus;
	int minus;
	int result;
};

#define SZ 3

int main(void)
{
	int i;
	struct PlusOrMinus pm[SZ] = { {2,2,0},{9,1,0},{7,5,0} };
	struct PlusOrMinus ph = { 4, 2, 0 };
	for ( i = 0; i < SZ; i++)
	{
		pm[i].minus = ph.plus * pm[i].plus;
		pm[i].plus = ph.minus * pm[i].minus;
		pm[i].result = i == 1 ?-2:2;
		printf("%d - %d - %d\n", pm[i].plus, pm[i].minus, pm[i].result);
		ph.minus++;
	}

	return 0;
}