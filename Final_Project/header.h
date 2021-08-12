

#define MAX_ACTIVITY_NAME_LEN 15
#define MAX_NAME_LEN 20
#define NUM_ACTIVITY_NAMES 3
#define MAX_PARTICIPANT 4
#define MAX_ACTIVITY 20

#include <stdio.h>
#include <string.h>


/* Structure declaration*/
struct Date
{
	int year;
	int month;
	int day;
};

struct Activity
{
	int activityType;
	double distance;
	struct Date date;
};

struct Participant
{
	char name[MAX_NAME_LEN + 1];
	struct Activity activities[MAX_ACTIVITY];
	int numActivities;
};

struct Individual
{
	char name[MAX_NAME_LEN + 1];
	double distance;
};



/* Function prototypes*/

// 1. scan data from text file and store values into local variables
int readActivityFile(FILE* fp, struct Participant participants[], const char activNames[][MAX_ACTIVITY_NAME_LEN + 1]);


// 2. find index number in the participants array according to the name given
int findParticipant(struct Participant participants[], int size, char name[]);


// 3. return a index number stand for activity name
int findString(const char activNames[][MAX_ACTIVITY_NAME_LEN + 1], int size, char activityName[]);


// 4. display menu function, returns a selected option number
int menu(void);


// 5. validate input number, must be an integer between 0-7
int validateInput(void);


// 6. convert numeric year, month, day into a day of the week
int zeller(const struct Date* date);


// 7. list all the activities for each participant
void listAll(struct Participant participants[], int participantsNum);


// 8. display individual's total distance by activity type and sorting
void totalDistance(struct Participant participants[], int participantsNum, int type);


// 9. display individual's best record by activity type and sorting
void topDistance(struct Participant participants[], int participantsNum, int type);
