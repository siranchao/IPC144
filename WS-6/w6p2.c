/*
	==================================================
	Workshop #6 (Part-2):
	==================================================
	Name   : Siran Cao
	ID     : 159235209
	Email  : scao34@myseneca.ca
	Section: NAA
*/

#define _CRT_SECURE_NO_WARNINGS

// System Libraries
#include<stdio.h>

// User Libraries
#include"w6p2.h"


// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
int getIntPositive(int* inputInt)
{
	int intNum = 0;
	if (inputInt != NULL)
	{
		scanf("%d", inputInt);
		while (*inputInt <= 0)
		{
			printf("ERROR: Enter a positive value: ");
			scanf("%d", inputInt);
		}
		return *inputInt;
	}
	else
	{
		scanf("%d", &intNum);
		while (intNum <= 0)
		{
			printf("ERROR: Enter a positive value: ");
			scanf("%d", &intNum);
		}
		return intNum;
	}
}

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
double getDoublePositive(double* inputDouble)
{
	double doubleNum = 0.0;
	if (inputDouble != NULL)
	{
		scanf("%lf", inputDouble);
		while (*inputDouble <= 0)
		{
			printf("ERROR: Enter a positive value: ");
			scanf("%lf", inputDouble);
		}
		return *inputDouble;
	}
	else
	{
		scanf("%lf", &doubleNum);
		while (doubleNum <= 0)
		{
			printf("ERROR: Enter a positive value: ");
			scanf("%lf", &doubleNum);
		}
		return doubleNum;
	}
}

// 3. Opening Message (include the number of products that need entering)
void openingMessage(const int productAmount)
{
	printf("Cat Food Cost Analysis\n"
		"======================\n\n");
	printf("Enter the details for %d dry food bags of product data for analysis.\n"
		"NOTE: A 'serving' is %dg\n\n", productAmount, SUGGEST_GRAMS);
}

// 4. Get user input for the details of cat food product
void getCatFoodInfo(struct CatFoodInfo infoArr[], const int productOrder)
{
	printf("Cat Food Product #%d\n"
		"--------------------\n", productOrder + 1);
	printf("SKU           : ");
	infoArr[productOrder].sku = getIntPositive(&infoArr[productOrder].sku);

	printf("PRICE         : $");
	infoArr[productOrder].price = getDoublePositive(&infoArr[productOrder].price);

	printf("WEIGHT (LBS)  : ");
	infoArr[productOrder].weight = getDoublePositive(NULL);

	printf("CALORIES/SERV.: ");
	infoArr[productOrder].calories = getIntPositive(NULL);
	printf("\n");
}

// 5. Display the formatted table header
void displayCatFoodHeader(void)
{
	printf("SKU         $Price    Bag-lbs Cal/Serv\n");
	printf("------- ---------- ---------- --------\n");
}

// 6. Display a formatted record of cat food data
void displayCatFoodData(const int sku, const double* price, const double* weight, const int calories)
{
	printf("%07d %10.2lf %10.1lf %8d\n", sku, *price, *weight, calories);
}

// 7. Logic entry point
void start(void)
{
	int i;
	int flag = 0;
	int cheapest = 0;
	struct CatFoodInfo infoArr[MAX_PRODUCTS] = { {0} };
	struct ReportData dataArr[MAX_PRODUCTS] = { { {0} } };
	
	//// Part 1
	openingMessage(MAX_PRODUCTS);
	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		getCatFoodInfo(infoArr, i);
	}

	displayCatFoodHeader();
	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		displayCatFoodData(infoArr[i].sku, &infoArr[i].price, &infoArr[i].weight, infoArr[i].calories);
	}
	printf("\n");

	//// Part 2 
	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		dataArr[i] = calculateReportData(infoArr[i]);
	}

	// find out the cheapest product
	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		if (dataArr[cheapest].costPerServing > dataArr[i].costPerServing)
		{
			cheapest = i;
		}
	}

	// Display the analysis report
	displayReportHeader();
	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		if (i == cheapest)
		{
			flag = 1;
			displayReportData(&dataArr[i], flag);
		}
		else
		{
			flag = 0;
			displayReportData(&dataArr[i], flag);
		}
	}
	printf("\n");

	displayFinalAnalysis(&infoArr[cheapest]);

}


// 8. convert weight in lbs to weight in kg
double convertLbsKg(const double* weightLbs, double* weightKg)
{
	if (weightKg != NULL)
	{
		*weightKg = *weightLbs / CONVERSION_RATE;
		return *weightKg;
	}
	else
	{
		return *weightLbs / CONVERSION_RATE;
	}
}

// 9. convert weight in lbs to weight in grams
int convertLbsG(const double* weightLbs, int* weightGrams)
{
	if (weightGrams != NULL)
	{
		*weightGrams = (int)(convertLbsKg(weightLbs, NULL) * 1000.00);
		return *weightGrams;
	}
	else
	{
		return (int)(convertLbsKg(weightLbs, NULL) * 1000.00);
	}

}

// 10. convert weight in lbs to weight in kg and grams at the same time
void convertLbs(const double* weightLbs, double* weightKg, int* weightGrams)
{
	*weightKg = convertLbsKg(weightLbs, NULL);
	*weightGrams = convertLbsG(weightLbs, NULL);
}

// 11. calculate the total servings based on serving size and total weight in grams
double calculateServings(const int servingSize, const int totalGrams, double* totalServings)
{
	if (totalServings != NULL)
	{
		*totalServings = (double)totalGrams / (double)servingSize;
		return *totalServings;
	}
	else
	{
		return (double)totalGrams / (double)servingSize;
	}
}

// 12. calculate cost per serving, based on product price and total servings
double calculateCostPerServing(const double* price, const double* totalServings, double* costPerServing)
{
	if (costPerServing != NULL)
	{
		*costPerServing = *price / *totalServings;
		return *costPerServing;
	}
	else
	{
		return *price / *totalServings;
	}
}

// 13. calculate cost per calories based on product price and total calories
double calculateCostPerCal(const double* price, const double totalCal, double* costPerCal)
{
	if (costPerCal != NULL)
	{
		*costPerCal = *price / totalCal;
		return *costPerCal;
	}
	else
	{
		return *price / totalCal;
	}
}

// 14. calculate the report data and pass to the address of structure data type
struct ReportData calculateReportData(const struct CatFoodInfo info)
{
	struct ReportData reportData = { {0} };
	
	reportData.basicInfo = info;
	reportData.weightKg = convertLbsKg(&info.weight, NULL);
	reportData.weightGrams = convertLbsG(&info.weight, NULL);
	reportData.totalServings = calculateServings(SUGGEST_GRAMS, reportData.weightGrams, NULL);
	reportData.costPerServing = calculateCostPerServing(&info.price, &reportData.totalServings, NULL);
	reportData.costPerCal = calculateCostPerCal(&info.price, info.calories * reportData.totalServings, NULL);
	
	return reportData;
}

// 15. display the report header
void displayReportHeader(void)
{
	printf("Analysis Report (Note: Serving = %dg\n", SUGGEST_GRAMS);
	printf("---------------\n");
	printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
	printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
}

// 16. display the overall report data
void displayReportData(const struct ReportData* reportData, const int flag)
{
	if (flag)
	{
		printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf ***\n", reportData->basicInfo.sku, reportData->basicInfo.price, reportData->basicInfo.weight, reportData->weightKg, reportData->weightGrams, reportData->basicInfo.calories, reportData->totalServings, reportData->costPerServing, reportData->costPerCal);
	}
	else
	{
		printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf\n", reportData->basicInfo.sku, reportData->basicInfo.price, reportData->basicInfo.weight, reportData->weightKg, reportData->weightGrams, reportData->basicInfo.calories, reportData->totalServings, reportData->costPerServing, reportData->costPerCal);
	}
}

// 17. display the final result of the cheapest product
void displayFinalAnalysis(const struct CatFoodInfo* info)
{
	printf("Final Analysis\n"
		   "--------------\n");
	printf("Based on the comparison data, the PURRR-fect economical option is:\n"
		   "SKU:%07d Price: $%.2lf\n\n", info->sku, info->price);
	printf("Happy shopping!\n\n");
}