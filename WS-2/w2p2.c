
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

int main(void)
{
	double enteredValue = 0.0;
	int totalCents = 0, serviceFee = 0, toonies = 0, loonies = 0, quarters = 0, dimes = 0, nickels = 0, pennies = 0;

	//input
	printf("Change Maker Machine\n"
			"====================\n"
			"Enter dollars and cents amount to convert to coins: $");
	
	scanf("%lf", &enteredValue);

	totalCents = (int)(enteredValue * 100);

	//service fee
	serviceFee = (int)(totalCents * .05 + .5);
	printf("Service fee (5.0 percent): %.2lf\n", (double)serviceFee / 100);

	//balance 
	totalCents -= serviceFee;
	printf("Balance to dispense: $%.2lf\n\n", (double)totalCents / 100);

	//coins
	toonies = (int)(totalCents / 200);
	totalCents %= 200;
	printf("$2.00 Toonies  X %d (remaining: $%.2lf)\n", toonies, (double)totalCents / 100);

	loonies = (int)(totalCents / 100);
	totalCents %= 100;
	printf("$1.00 Loonies  X %d (remaining: $%.2lf)\n", loonies, (double)totalCents / 100);

	quarters = (int)(totalCents / 25);
	totalCents %= 25;
	printf("$0.25 Quarters X %d (remaining: $%.2lf)\n", quarters, (double)totalCents / 100);

	dimes = (int)(totalCents / 10);
	totalCents %= 10;
	printf("$0.10 Dimes    X %d (remaining: $%.2lf)\n", dimes, (double)totalCents / 100);

	nickels = (int)(totalCents / 5);
	totalCents %= 5;
	printf("$0.05 Nickels  X %d (remaining: $%.2lf)\n", nickels, (double)totalCents / 100);

	pennies = (int)(totalCents / 1);
	totalCents %= 1;
	printf("$0.01 Pennies  X %d (remaining: $%.2lf)\n\n", pennies, (double)totalCents / 100);

	if (totalCents == 0)
	{
		printf("All coins dispensed!\n");
	}

	return 0;
}
