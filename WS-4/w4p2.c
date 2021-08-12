/*
	==================================================
	Workshop #4 (Part-2):
	==================================================
	Name   : Siran Cao
	ID     : 159235209
	Email  : scao34@myseneca.ca
	Section: NAA
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define MAX_INCOME 400000.00
#define MIN_INCOME 500.00
#define MAX_ITEM 10
#define MIN_ITEM 1
#define MIN_ITEMCOST 100.00

int main(void)
{

	double netIncome = 0.0, itemCost = 0.0, totalCost = 0.0, eachGroupCost;
	char financed = '0';
	int items = 0, priority = 0, option = 0, years = 0, months = 0, prioritySelected = 0;
	int i;
	int flag = 0, found = 0;

	double costList[MAX_ITEM] = { 0.0 };
	int priorityList[MAX_ITEM] = { 0 };
	char financeList[MAX_ITEM] = { 0 };


	printf("+--------------------------+\n"
		   "+   Wish List Forecaster   |\n"
		   "+--------------------------+\n\n");

	//Input monthly income
	while (!flag)
	{
		printf("Enter your monthly NET income: $");
		scanf(" %lf", &netIncome);

		if (netIncome < MIN_INCOME)
		{
			printf("ERROR: You must have a consistent monthly income of at least $500.00\n\n");
		}
		else if (netIncome > MAX_INCOME)
		{
			printf("ERROR: Liar! I'll believe you if you enter a value no more than $400000.00\n\n");
		}
		else
		{
			printf("\n");
			flag = 1;
		}
	}

	//Input item numbers
	flag = 0;
	while (!flag)
	{
		printf("How many wish list items do you want to forecast?: ");
		scanf(" %d", &items);

		if (items <= MAX_ITEM && items >= MIN_ITEM)
		{
			printf("\n");
			flag = 1;
		}
		else
		{
			printf("ERROR: List is restricted to between 1 and 10 items.\n\n");
		}
	}

	//Details for each item
	for (i = 0; i < items; i++)
	{
		printf("Item-%d Details:\n", i + 1);

		flag = 0;
		while (!flag)
		{
			printf("   Item cost: $");
			scanf(" %lf", &itemCost);
			if (itemCost >= MIN_ITEMCOST)
			{
				costList[i] = itemCost;
				flag = 1;
			}
			else
			{
				printf("      ERROR: Cost must be at least $100.00\n");
			}
		}

		flag = 0;
		while (!flag)
		{
			printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
			scanf(" %d", &priority);
			if (priority >= 1 && priority <= 3)
			{
				priorityList[i] = priority;
				flag = 1;
			}
			else
			{
				printf("      ERROR: Value must be between 1 and 3\n");
			}
		}

		flag = 0;
		while (!flag)
		{
			printf("   Does this item have financing options? [y/n]: ");
			scanf(" %c", &financed);
			if (financed == 'y' || financed == 'n')
			{
				financeList[i] = financed;
				flag = 1;
			}
			else
			{
				printf("      ERROR: Must be a lowercase 'y' or 'n'\n");
			}
		}
		printf("\n");
	}

	//Display formatted table
	printf("Item Priority Financed        Cost\n");
	printf("---- -------- -------- -----------\n");
	for (i = 0; i < items; i++)
	{
		printf("%3d  %5d    %5c    %11.2lf\n", i + 1, priorityList[i], financeList[i], costList[i]);
		totalCost += costList[i];
	}
	printf("---- -------- -------- -----------\n");
	printf("                      $%11.2lf\n", totalCost);



	//Display menu of options (part-2)
	flag = 0;
	while (!flag)
	{
		printf("\nHow do you want to forecast your wish list?\n"
			   " 1. All items (no filter)\n"
		       " 2. By priority\n"
		       " 0. Quit/Exit\n"
		       "Selection: ");
		scanf(" %d", &option);

		if (option == 1) ////When choose option 1
		{
			printf("\n");
			printf("====================================================\n");
			printf("Filter:   All items\n");
			printf("Amount:   $%1.2lf\n", totalCost);
			
			years = (int)(totalCost / netIncome / 12);
			months = (int)(totalCost / netIncome + 1) % 12;
			printf("Forecast: %d years, %d months\n", years, months);

			found = 0;
			for (i = 0; i < items && !found; i++)
			{
				if (financeList[i] == 'y')
				{
					printf("NOTE: Financing options are available on some items.\n"
					       "      You can likely reduce the estimated months.\n");
					found = 1;
				}
			}
			printf("====================================================\n");
		}
		else if (option == 2) ////When choose option 2
		{
			found = 0;
			while (!found)
			{
				printf("\nWhat priority do you want to filter by? [1-3]: ");
				scanf(" %d", &prioritySelected);
				if (prioritySelected >= 1 && prioritySelected <= 3)
				{
					found = 1;
				}
				else
				{
					printf("\nError: please select your priority level between [1-3] \n");
				}
			}
			printf("\n");
			printf("====================================================\n");
			printf("Filter:   by priority (%d)\n", prioritySelected);

			eachGroupCost = 0.0;
			for (i = 0; i < items; i++)
			{
				if (priorityList[i] == prioritySelected)
				{
					eachGroupCost += costList[i];
				}
			}
			printf("Amount:   $%1.2lf\n", eachGroupCost);
			
			years = (int)(eachGroupCost / netIncome / 12);
			months = (int)(eachGroupCost / netIncome + 1) % 12;
			printf("Forecast: %d years, %d months\n", years, months);

			found = 0;
			for (i = 0; i < items && !found; i++)
			{
				if (priorityList[i] == prioritySelected)
				{
					if (financeList[i] == 'y')
					{
						printf("NOTE: Financing options are available on some items.\n"
							"      You can likely reduce the estimated months.\n");
						found = 1;
					}
				}
			}
			printf("====================================================\n");

		}
		else if (option == 0) ////When choose option 0
		{
			printf("\n");
			printf("Best of luck in all your future endeavours!\n");
			flag = 1;
		}
		else
		{
			printf("\n");
			printf("ERROR: Invalid menu selection.\n");
		}
	

	}

	return 0;
}