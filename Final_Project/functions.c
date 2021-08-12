

#define _CRT_SECURE_NO_WARNINGS

#include "header.h"



/* Function definitions*/

// 1.
int readActivityFile(FILE* fp, struct Participant participants[], const char activNames[][MAX_ACTIVITY_NAME_LEN + 1])
{
    int count = 0, ch, addPosn, actPosn;
    char activity[16];
    char name[MAX_NAME_LEN + 1];
    int year = 0, month = 0, day = 0;
    double dist = 0.0;

    while (!feof(fp))
    {
        fscanf(fp, "%[^~]s%*c", name);
        ch = fgetc(fp);
        fscanf(fp, "%[^~]s%*c", activity);
        ch = fgetc(fp);
        fscanf(fp, "%d", &year);
        ch = fgetc(fp);
        fscanf(fp, "%d", &month);
        ch = fgetc(fp);
        fscanf(fp, "%d", &day);
        ch = fgetc(fp);
        fscanf(fp, "%lf", &dist);
        ch = fgetc(fp);

        addPosn = findParticipant(participants, count, name);

        if (addPosn < 0)
        {
            addPosn = count;
            participants[addPosn].numActivities = 0;
            strcpy(participants[addPosn].name, name);
            count++;
        }

        actPosn = participants[addPosn].numActivities;

        participants[addPosn].activities[actPosn].activityType = findString(activNames, NUM_ACTIVITY_NAMES, activity);
        participants[addPosn].activities[actPosn].date.year = year;
        participants[addPosn].activities[actPosn].date.month = month;
        participants[addPosn].activities[actPosn].date.day = day;
        participants[addPosn].activities[actPosn].distance = dist;
        participants[addPosn].numActivities++;

        ch = fgetc(fp);
        if (!feof(fp)) ungetc(ch, fp);
    }

    return count;
}


// 2.
int findParticipant(struct Participant participants[], int count, char name[])
{
    int i;
    int flag = 0, position = -1;

    for (i = 0; i < count && !flag; i++)
    {
        if (strcmp(name, participants[i].name) == 0)
        {
            position = i;
            flag = 1;
        }
    }
    return position;
}


// 3.
int findString(const char activNames[][MAX_ACTIVITY_NAME_LEN + 1], int size, char activityName[])
{
    int i;
    int flag = 0, value = -1;

    for (i = 0; i < size && !flag; i++)
    {
        if (strcmp(activNames[i], activityName) == 0)
        {
            value = i;
            flag = 1;
        }
    }
    return value;
}


// 4.
int menu(void)
{
    int option;
    printf("Select one of the following options:\n"
        "0 - Exit\n"
        "1 - list all participants and events\n"
        "2 - list total run distances\n"
        "3 - list total swim distances\n"
        "4 - list total bike distances\n"
        "5 - list best run distances\n"
        "6 - list best swim distances\n"
        "7 - list best bike distances\n");
    option = validateInput();

    return option;
}


// 5.
int validateInput(void)
{
    int inputInt = 0, flag = 0;

    while (!flag)
    {
        scanf("%d", &inputInt);

        if (inputInt < 0 || inputInt > 7)
        {
            while (getchar() != '\n');
            printf("Enter a number between 0 and 7: ");    
        }
        else
        {
            flag = 1;
        }
    }
    return inputInt;
}


// 6. 
int zeller(const struct Date* date)
{
    int month = date->month;
    int year = date->year;

    if (date->month < 3)
    {
        year--;
        month += 12;
    }

    int yr = year % 100;
    int century = year / 100;
    int result = date->day;

    result += 13 * (month + 1) / 5;
    result += yr;
    result += yr / 4;
    result += century / 4;
    result -= 2 * century;
    result = result % 7;

    return result;
}



// 7.
void listAll(struct Participant participants[], int participantsNum)
{
    int i, k;
    char day[5];
    char month[5];
    char activity[MAX_ACTIVITY_NAME_LEN];

    for (i = 0; i < participantsNum; i++)
    {
        printf("%s\n", participants[i].name);
        printf("----------------------------------------------\n");

        for (k = 0; k < participants[i].numActivities; k++)
        {
            switch (zeller(&participants[i].activities[k].date))
            {
            case 0:
                strcpy(day, "Sat");
                break;
            case 1:
                strcpy(day, "Sun");
                break;
            case 2:
                strcpy(day, "Mon");
                break;
            case 3:
                strcpy(day, "Tue");
                break;
            case 4:
                strcpy(day, "Wed");
                break;
            case 5:
                strcpy(day, "Thu");
                break;
            case 6:
                strcpy(day, "Fri");
                break;
            }

            switch (participants[i].activities[k].date.month)
            {
            case 1:
                strcpy(month, "Jan");
                break;
            case 2:
                strcpy(month, "Feb");
                break;
            case 3:
                strcpy(month, "Mar");
                break;
            case 4:
                strcpy(month, "Apr");
                break;
            case 5:
                strcpy(month, "May");
                break;
            case 6:
                strcpy(month, "Jun");
                break;
            case 7:
                strcpy(month, "Jul");
                break;
            case 8:
                strcpy(month, "Aug");
                break;
            case 9:
                strcpy(month, "Sep");
                break;
            case 10:
                strcpy(month, "Oct");
                break;
            case 11:
                strcpy(month, "Nov");
                break;
            case 12:
                strcpy(month, "Dec");
                break;
            }

            switch (participants[i].activities[k].activityType)
            {
            case 0:
                strcpy(activity, "run");
                break;
            case 1:
                strcpy(activity, "swim");
                break;
            case 2:
                strcpy(activity, "bike");
                break;
            }

            printf("%5s %s %s %d %5.1lf\n", activity, day, month, participants[i].activities[k].date.day, participants[i].activities[k].distance);
        }
        printf("\n");
    }
}



// 8.
void totalDistance(struct Participant participants[], int participantsNum, int type)
{
    char activity[MAX_ACTIVITY_NAME_LEN];
    double total;
    int i, k;
    struct Individual totalDistList[MAX_PARTICIPANT] = { 0 };
    struct Individual temp1 = { 0 };

    switch (type)
    {
    case 0:
        strcpy(activity, "RUNS");
        break;
    case 1:
        strcpy(activity, "SWIMS");
        break;
    case 2:
        strcpy(activity, "BIKES");
        break;
    }

    // store individual's total distance
    for (i = 0; i < participantsNum; i++)
    {
        total = 0.0;

        for (k = 0; k < participants[i].numActivities; k++)
        {
            if (participants[i].activities[k].activityType == type)
            {
                total += participants[i].activities[k].distance;
            }
        }

        strcpy(totalDistList[i].name, participants[i].name);
        totalDistList[i].distance = total;
    }

    // descending order for totalDist array
    for (i = participantsNum - 1; i > 0; i--)
    {
        for (k = 0; k < i; k++)
        {
            if (totalDistList[k].distance < totalDistList[k+1].distance)
            {
                temp1 = totalDistList[k];
                totalDistList[k] = totalDistList[k + 1];
                totalDistList[k + 1] = temp1;
            }
        }
    }
    // display header
    printf("    *** TOTAL %s ***\n", activity);

    // display list
    for (i = 0; i < participantsNum; i++)
    {
        printf("%15s %6.1f\n", totalDistList[i].name, totalDistList[i].distance + 0.005);
    }
    printf("\n");

}



// 9.
void topDistance(struct Participant participants[], int participantsNum, int type)
{
    char activity[MAX_ACTIVITY_NAME_LEN];
    double max;
    int i, k, j, count;
    double distList[MAX_ACTIVITY];
    struct Individual topDistList[MAX_PARTICIPANT] = { 0 };
    struct Individual temp2 = { 0 };

    switch (type)
    {
    case 0:
        strcpy(activity, "RUNS");
        break;
    case 1:
        strcpy(activity, "SWIMS");
        break;
    case 2:
        strcpy(activity, "BIKES");
        break;
    }

    // loop over each participant
    for (i = 0; i < participantsNum; i++)
    {
        // clear the temp data
        max = 0.0;
        count = 0;
        for (j = 0; j < MAX_ACTIVITY; j++)
        {
            distList[j] = 0.0;
        }

        // filter distance data into array by each activity
        for (k = j = 0; k < participants[i].numActivities; k++)
        {
            if (participants[i].activities[k].activityType == type)
            {         
                distList[j] = participants[i].activities[k].distance; 
                count++;
                j++;
            }
        }

        // find out the max number
        max = distList[0];
        for (j = 0; j < count; j++)
        {
            if (max < distList[j+1])
            {
                max = distList[j+1];
            }
        }

        // give values to the structure array
        strcpy(topDistList[i].name, participants[i].name);
        topDistList[i].distance = max;
    }

    // descending order for topDist array
    for (i = participantsNum - 1; i > 0; i--)
    {
        for (k = 0; k < i; k++)
        {
            if (topDistList[k].distance < topDistList[k + 1].distance)
            {
                temp2 = topDistList[k];
                topDistList[k] = topDistList[k + 1];
                topDistList[k + 1] = temp2;
            }
        }
    }

    // display header
    printf("    *** TOP %s ***\n", activity);

    // display list
    for (i = 0; i < participantsNum; i++)
    {
        printf("%15s %6.1lf\n", topDistList[i].name, topDistList[i].distance + 0.005);
    }
    printf("\n");

}
