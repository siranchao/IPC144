//==============================================
// Name:           Siran Cao
// Student Number: 159235209
// Email:          scao34@myseneca.ca
// Section:        NAA
// Date:           
//==============================================
// Assignment:     2
// Milestone:      4
//==============================================

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include"contactHelpers.h"

#define MAXCONTACTS 5

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        contents below...                        |
// +-------------------------------------------------+

// Clear the standard input buffer
void clearKeyboard(void)
{
    while (getchar() != '\n'); // empty execution code block on purpose
}

// pause function definition goes here:
void pause(void)
{
    printf("(Press Enter to Continue)");
    clearKeyboard();
}

// getInt function definition goes here:
int getInt(void)
{
    int inputInt = 0;
    char newline = 0;

    while (newline != '\n')
    {
        scanf("%d%c", &inputInt, &newline);

        if (newline != '\n')
        {
            clearKeyboard();
            printf("*** INVALID INTEGER *** <Please enter an integer>: ");
        }
    }
    return inputInt;
}

// getIntInRange function definition goes here:
int getIntInRange(int min, int max)
{
    int integer = 0, flag = 0;

    while (!flag)
    {
        integer = getInt();

        if (integer >= min && integer <= max)
        {
            flag = 1;
        }
        else
        {
            printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
        }
    }
    return integer;
}

// yes function definition goes here:
int yes(void)
{
    int value = 0, flag = 0;
    char inputChar = 0, newline = 0;

    while (!flag)
    {
        scanf("%c%c", &inputChar, &newline);

        if (newline != '\n')
        {
            clearKeyboard();
            printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
        }
        else
        {
            switch (inputChar)
            {
            case 'y':
            case 'Y':
                flag = 1;
                value = 1;
                break;
            case 'n':
            case 'N':
                flag = 1;
                value = 0;
                break;
            default:
                printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
                break;
            }
        }
    }
    return value;
}

// menu function definition goes here:
int menu(void)
{
    printf("Contact Management System\n"
        "-------------------------\n"
        "1. Display contacts\n"
        "2. Add a contact\n"
        "3. Update a contact\n"
        "4. Delete a contact\n"
        "5. Search contacts by cell phone number\n"
        "6. Sort contacts by cell phone number\n"
        "0. Exit\n\n");
    printf("Select an option:> ");

    return getIntInRange(0, 6);
}

// contactManagerSystem function definition goes here:
void contactManagerSystem(void)
{
    int option;
    int flag = 0;
    struct Contact contacts[MAXCONTACTS] = 
    { 
        { { "Rick", {'\0'}, "Grimes" }, 
        { 11, "Trailer Park", 0, "A7A 2J2", "King City" }, 
        { "4161112222", "4162223333", "4163334444" } },
        
        { { "Maggie", "R.", "Greene" },
        { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
        { "9051112222", "9052223333", "9053334444" } },

        { { "Morgan", "A.", "Jones" },
        { 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
        { "7051112222", "7052223333", "7053334444" } },

        { { "Sasha", {'\0'}, "Williams" },
        { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
        { "9052223333", "9052223333", "9054445555" } },
    };


    while (!flag)
    {
        option = menu();

        switch (option)
        {
        case 1:
            displayContacts(contacts, MAXCONTACTS);
            pause();
            break;
        case 2:
            addContact(contacts, MAXCONTACTS);
            pause();
            break;
        case 3:
            updateContact(contacts, MAXCONTACTS);
            pause();
            break;
        case 4:
            deleteContact(contacts, MAXCONTACTS);
            pause();
            break;
        case 5:
            searchContacts(contacts, MAXCONTACTS);
            pause();
            break;
        case 6:
            sortContacts(contacts, MAXCONTACTS);
            pause();
            break;
        case 0:
            printf("\nExit the program? (Y)es/(N)o: ");
            if (yes() == 1)
            {
                printf("\nContact Management System: terminated\n");
                flag = 1;
                break;
            }
            else
            {
                break;
            }
        }
        printf("\n");

    }
}



// Generic function to get a ten-digit phone number (ensures 10-digit chars entered)
// ---------------------------------------------------------------------------------
// NOTE: Modify this function to validate only numeric character digits are entered
// ---------------------------------------------------------------------------------
void getTenDigitPhone(char phoneNum[11])
{
    int needInput = 1, sum = 0;
    int i;

    while (needInput == 1)
    {
        scanf("%10s", phoneNum);
        clearKeyboard();

        for (i = 0; i < strlen(phoneNum); i++)
        {
            if (isdigit(phoneNum[i]) != 0)
            {
                sum++;
            }
        }

        if (sum == 10 && strlen(phoneNum) == 10)
        {
            needInput = 0;
        }
        else
        {
            sum = 0;
            printf("Enter a 10-digit phone number: ");
        }

    }
}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
    int i;
    int flag = 0;

    for (i = 0; i < size && !flag; i++)
    {
        if (strcmp(contacts[i].numbers.cell, cellNum) == 0)
        {
            flag = 1;
            return i;
        }
    }

    return -1;
}


// displayContactHeader
void displayContactHeader(void)
{
    int i;

    // line 1
    printf("\n+");
    for (i = 0; i < 77; i++)
    {
        printf("-");
    }
    printf("+\n");

    // line 2
    printf("|");
    for (i = 0; i < 30; i++)
    {
        printf(" ");
    }
    printf("Contacts Listing");
    for (i = 0; i < 31; i++)
    {
        printf(" ");
    }
    printf("|\n");

    // line 3
    printf("+");
    for (i = 0; i < 77; i++)
    {
        printf("-");
    }
    printf("+\n");
}


// displayContactFooter:
void displayContactFooter(int count)
{
    int i;

    // line 1
    printf("+");
    for (i = 0; i < 77; i++)
    {
        printf("-");
    }
    printf("+\n");

    //line 2
    printf("Total contacts: %d\n\n", count);
}


// displayContact:
void displayContact(const struct Contact* contact)
{
    // line 1
    if (contact->name.middleInitial[0] != '\0')
    {
        printf(" %s %s %s\n", contact->name.firstName, contact->name.middleInitial, contact->name.lastName);
    }
    else
    {
        printf(" %s %s\n", contact->name.firstName, contact->name.lastName);
    }

    // line 2
    printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);

    // line 3
    if (contact->address.apartmentNumber != 0)
    {
        printf("       %d %s, Apt# %d, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.apartmentNumber, contact->address.city, contact->address.postalCode);
    }
    else
    {
        printf("       %d %s, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.city, contact->address.postalCode);
    }
}


// displayContacts:
void displayContacts(const struct Contact contacts[], int size)
{
    int i;
    int validContacts = 0;

    displayContactHeader();

    for (i = 0; i < size; i++)
    {
        if (contacts[i].numbers.cell[0] != '\0')
        {
            validContacts++;
            displayContact(&contacts[i]);
        }

    }

    displayContactFooter(validContacts);
}


// searchContacts:
void searchContacts(const struct Contact contacts[], int size)
{
    char cellNum[11];
    int index;

    printf("\nEnter the cell number for the contact: ");
    getTenDigitPhone(cellNum);

    index = findContactIndex(contacts, size, cellNum);

    if (index != -1)
    {
        printf("\n");
        displayContact(&contacts[index]);
        printf("\n");
    }
    else
    {
        printf("*** Contact NOT FOUND ***\n\n");
    }
}


// addContact:
void addContact(struct Contact contacts[], int size)
{
    int index = 0, found = 0;
    int i;

    for (i = 0; i < size && !found; i++)
    {
        if (contacts[i].numbers.cell[0] == '\0')
        {
            index = i;
            found = 1;
        }
    }

    if (found)
    {
        printf("\n");
        getContact(&contacts[index]);
        printf("--- New contact added! ---\n\n");
    }
    else
    {
        printf("\n*** ERROR: The contact list is full! ***\n\n");
    }
}


// updateContact:
void updateContact(struct Contact contacts[], int size)
{
    char cellNum[11];
    int index, answer;

    printf("\nEnter the cell number for the contact: ");
    getTenDigitPhone(cellNum);
    
    index = findContactIndex(contacts, size, cellNum);

    if (index == -1)
    {
        printf("*** Contact NOT FOUND ***\n\n");
    }
    else
    {
        printf("\nContact found:\n");
        displayContact(&contacts[index]);
        printf("\n");

        printf("Do you want to update the name? (y or n): ");
        answer = yes();
        if (answer == 1)
        {
            getName(&contacts[index].name);
        }

        printf("Do you want to update the address? (y or n): ");
        answer = yes();
        if (answer == 1)
        {
            getAddress(&contacts[index].address);
        }

        printf("Do you want to update the numbers? (y or n): ");
        answer = yes();
        if (answer == 1)
        {
            getNumbers(&contacts[index].numbers);
        }

        printf("--- Contact Updated! ---\n\n");
    }
}


// deleteContact:
void deleteContact(struct Contact contacts[], int size)
{
    char cellNum[11];
    int index, answer;

    printf("\nEnter the cell number for the contact: ");
    getTenDigitPhone(cellNum);

    index = findContactIndex(contacts, size, cellNum);

    if (index == -1)
    {
        printf("*** Contact NOT FOUND ***\n");
    }
    else
    {
        printf("\nContact found:\n");
        displayContact(&contacts[index]);
        printf("\n");

        printf("CONFIRM: Delete this contact? (y or n): ");
        answer = yes();
        if (answer == 1)
        {
            contacts[index].numbers.cell[0] = '\0';
            printf("--- Contact deleted! ---\n");
        }
    }
    printf("\n");
}


// sortContacts:
void sortContacts(struct Contact contacts[], int size)
{
    int i, j;
    int k = 0;
    struct Contact tempContact = { { {0} } };

    for (i = size - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            //TEST - 1

            if (contacts[j].numbers.cell[k] > contacts[j+1].numbers.cell[k])
            {
                tempContact = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = tempContact;
            }
            else if (contacts[j].numbers.cell[k] == contacts[j + 1].numbers.cell[k])
            {
                if (contacts[j].numbers.cell[k+1] > contacts[j + 1].numbers.cell[k+1])
                {
                    tempContact = contacts[j];
                    contacts[j] = contacts[j + 1];
                    contacts[j + 1] = tempContact;
                }
                else if (contacts[j].numbers.cell[k+1] == contacts[j + 1].numbers.cell[k+1])
                {
                    if (contacts[j].numbers.cell[k+2] > contacts[j + 1].numbers.cell[k+2])
                    {
                        tempContact = contacts[j];
                        contacts[j] = contacts[j + 1];
                        contacts[j + 1] = tempContact;
                    }
                }
            }

            //TEST - 2
           
            //for (k = 0; k < 10 && !flag; k++)
            //{
            //    if (contacts[j].numbers.cell[k] > contacts[j + 1].numbers.cell[k]) {
            //        tempContact = contacts[j];
            //        contacts[j] = contacts[j + 1];
            //        contacts[j + 1] = tempContact;
            //        flag = 1;
            //    }
            //    else if (contacts[j].numbers.cell[k] == contacts[j + 1].numbers.cell[k]) {
            //    }
            //    else {
            //        flag = 1;
            //    }
            //}

        }
    }
    printf("\n--- Contacts sorted! ---\n\n");
}
