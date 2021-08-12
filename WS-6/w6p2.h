


#define MAX_PRODUCTS 3
#define SUGGEST_GRAMS 64
#define CONVERSION_RATE 2.20462

// ----------------------------------------------------------------------------
// structures
struct CatFoodInfo
{
	int sku;
	double price;
	int calories;
	double weight;
};

struct ReportData
{
	struct CatFoodInfo basicInfo;
	double weightKg;
	int weightGrams;
	double totalServings;
	double costPerServing;
	double costPerCal;
};


// ----------------------------------------------------------------------------
// function prototypes

// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
int getIntPositive(int* inputInt);

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
double getDoublePositive(double* inputDouble);

// 3. Opening Message (include the number of products that need entering)
void openingMessage(const int productAmount);

// 4. Get user input for the details of cat food product
void getCatFoodInfo(struct CatFoodInfo info[], const int productOrder);

// 5. Display the formatted table header
void displayCatFoodHeader(void);

// 6. Display a formatted record of cat food data
void displayCatFoodData(const int sku, const double* price, const double* weight, const int calories);

// 7. Logic entry point
void start(void);

// 8. convert weight in lbs to weight in kg
double convertLbsKg(const double* weightLbs, double* weightKg);

// 9. convert weight in lbs to weight in grams
int convertLbsG(const double* weightLbs, int* weightGrams);

// 10. convert weight in lbs to weight in kg and grams at the same time
void convertLbs(const double* weightLbs, double* weightKg, int* weightGrams);

// 11. calculate the total servings based on serving size and total weight in grams
double calculateServings(const int servingSize, const int totalGrams, double* totalServings);

// 12. calculate cost per serving, based on product price and total servings
double calculateCostPerServing(const double* price, const double* totalServings, double* costPerServing);

// 13. calculate cost per calories based on product price and total calories
double calculateCostPerCal(const double* price, const double totalCal, double* costPerCal);

// 14. calculate the report data and pass to the address of structure data type
struct ReportData calculateReportData(const struct CatFoodInfo info);

// 15. display the report header
void displayReportHeader(void);

// 16. display the overall report data
void displayReportData(const struct ReportData* reportData, const int flag);

// 17. display the final result of the cheapest product
void displayFinalAnalysis(const struct CatFoodInfo* info);
