
#define _CRT_SECURE_NO_WARNINGS


#include "header.h"


int main(void)
{
	struct Participant participants[MAX_PARTICIPANT] = { 0 }; 
	char activNames[][MAX_ACTIVITY_NAME_LEN + 1] = { "run", "swim", "bike" };

	int participantsNum, option;
	int flag = 0;


	FILE* fp = NULL;
	fp = fopen("data.txt", "r");
	if (fp != NULL)
	{
		readActivityFile(fp, participants, activNames);

		fclose(fp);
	}
	else
	{
		printf("Fail to open file\n");
	}

	participantsNum = sizeof(participants) / sizeof(participants[0]);
	printf("Read %d participants\n\n", participantsNum);
	
	while (!flag)
	{
		option = menu();

		switch (option)
		{
		case 0:
			printf("Goodbye\n");
			flag = 1;
			break;
		case 1:
			listAll(participants, participantsNum);
			break;
		case 2:
			totalDistance(participants, participantsNum, 0);
			break;
		case 3:
			totalDistance(participants, participantsNum, 1);
			break;
		case 4:
			totalDistance(participants, participantsNum, 2);
			break;
		case 5:
			topDistance(participants, participantsNum, 0);
			break;
		case 6:
			topDistance(participants, participantsNum, 1);
			break;
		case 7:
			topDistance(participants, participantsNum, 2);
			break;
		}
	}


	return 0;
}
