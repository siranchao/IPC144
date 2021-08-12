
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define MAX_YEAR 2010
#define MIN_YEAR 2021
#define LOG_DAYS 3


int main(void)
{
	const int jan = 1, dec = 12;
	int enteredYear = 0, enteredMonth = 0;
	char letter1, letter2, letter3;
	int i;
	double morningRate = 10.0, eveningRate = 10.0, morningTotalRating = 0.0, eveningTotalRating = 0.0;


	// Log date informations:
	printf("General Well-being Log\n"
		"======================\n");

	while (enteredYear > 2021 || enteredYear<2010 || enteredMonth>dec || enteredMonth < jan)
	{
		printf("Set the year and month for the well-being log (YYYY MM): ");
		scanf("%d %d", &enteredYear, &enteredMonth);

		if (enteredYear > 2021 || enteredYear < 2010)
		{
			printf("   ERROR: The year must be between 2010 and 2021 inclusive\n");
		}
		if (enteredMonth > dec || enteredMonth < jan)
		{
			printf("   ERROR: Jan.(1) - Dec.(12)\n");
		}
	}

	printf("\n*** Log date set! ***\n\n");

	switch (enteredMonth)
	{
	case 1:
		letter1 = 'J', letter2 = 'A', letter3 = 'N';
		break;
	case 2:
		letter1 = 'F', letter2 = 'E', letter3 = 'B';
		break;
	case 3:
		letter1 = 'M', letter2 = 'A', letter3 = 'R';
		break;
	case 4:
		letter1 = 'A', letter2 = 'P', letter3 = 'R';
		break;
	case 5:
		letter1 = 'M', letter2 = 'A', letter3 = 'Y';
		break;
	case 6:
		letter1 = 'J', letter2 = 'U', letter3 = 'N';
		break;
	case 7:
		letter1 = 'J', letter2 = 'U', letter3 = 'L';
		break;
	case 8:
		letter1 = 'A', letter2 = 'U', letter3 = 'G';
		break;
	case 9:
		letter1 = 'S', letter2 = 'E', letter3 = 'P';
		break;
	case 10:
		letter1 = 'O', letter2 = 'C', letter3 = 'T';
		break;
	case 11:
		letter1 = 'N', letter2 = 'O', letter3 = 'V';
		break;
	case 12:
		letter1 = 'D', letter2 = 'E', letter3 = 'C';
		break;
	default:
		break;
	}


	// Display daily ratings:
	for (i = 0; i < LOG_DAYS; i++)
	{
		printf("%d-%c%c%c-%02d\n", enteredYear, letter1, letter2, letter3, i + 1);

		//input morning rating
		printf("   Morning rating (0.0-5.0): ");
		scanf("%lf", &morningRate);
		while (morningRate > 5.0 || morningRate < 0.0)
		{
			printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!\n");
			printf("   Morning rating (0.0-5.0): ");
			scanf("%lf", &morningRate);
		}
		morningTotalRating += morningRate;

		//input evening rating
		printf("   Evening rating (0.0-5.0): ");
		scanf("%lf", &eveningRate);
		while (eveningRate > 5.0 || eveningRate < 0.0)
		{
			printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!\n");
			printf("   Evening rating (0.0-5.0): ");
			scanf("%lf", &eveningRate);
		}
		eveningTotalRating += eveningRate;
		printf("\n");

	}

	// Summary part
	printf("Summary\n"
		   "=======\n");
	
	printf("Morning total rating: %.3lf\n", morningTotalRating);
	printf("Evening total rating: %.3lf\n", eveningTotalRating);
	printf("----------------------------\n");
	printf("Overall total rating: %.3lf\n", morningTotalRating + eveningTotalRating);
	
	printf("\n");

	printf("Average morning rating:  %.1lf\n", morningTotalRating / LOG_DAYS);
	printf("Average evening rating:  %.1lf\n", eveningTotalRating / LOG_DAYS);
	printf("----------------------------\n");
	printf("Average overall rating:  %.1lf\n", (morningTotalRating + eveningTotalRating) / LOG_DAYS / 2);


	return 0;
}
