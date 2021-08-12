

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "contacts.h"
#include "contactHelpers.h"

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        source code below...                     |
// +-------------------------------------------------+

void getName(struct Name* name)
{
    int answer;

    printf("Please enter the contact's first name: ");
    scanf("%30[^\n]", name->firstName);
    clearKeyboard();

    printf("Do you want to enter a middle initial(s)? (y or n): ");
    answer = yes();

    if (answer == 1)
    {
        printf("Please enter the contact's middle initial(s): ");
        scanf("%6[^\n]", name->middleInitial);
        clearKeyboard();
    }
    else
    {
        name->middleInitial[0] = '\0';
    }
    printf("Please enter the contact's last name: ");
    scanf("%35[^\n]", name->lastName);
    clearKeyboard();
}


void getAddress(struct Address* address)
{
    int answer;

    printf("Please enter the contact's street number: ");
    address->streetNumber = getInt();

    while (address->streetNumber < 1)
    {
        printf("*** INVALID STREET NUMBER *** <must be a positive number>: ");
        address->streetNumber = getInt();
    }

    printf("Please enter the contact's street name: ");
    scanf("%40[^\n]", address->street);
    clearKeyboard();

    printf("Do you want to enter an apartment number? (y or n): ");
    answer = yes();

    if (answer == 1)
    {
        printf("Please enter the contact's apartment number: ");
        address->apartmentNumber = getInt();

        while (address->apartmentNumber < 1)
        {
            printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");
            address->apartmentNumber = getInt();
        }
    }
    else
    {
        address->apartmentNumber = 0;
    }

    printf("Please enter the contact's postal code: ");
    scanf("%7[^\n]", address->postalCode);
    clearKeyboard();

    printf("Please enter the contact's city: ");
    scanf("%40[^\n]", address->city);
    clearKeyboard();
}


void getNumbers(struct Numbers* numbers)
{
    int answer;

    printf("Please enter the contact's cell phone number: ");
    getTenDigitPhone(numbers->cell);

    printf("Do you want to enter a home phone number? (y or n): ");
    answer = yes();

    if (answer == 1)
    {
        printf("Please enter the contact's home phone number: ");
        getTenDigitPhone(numbers->home);
    }
    else
    {
        numbers->home[0] = '\0';
    }

    printf("Do you want to enter a business phone number? (y or n): ");
    answer = yes();

    if (answer == 1)
    {
        printf("Please enter the contact's business phone number: ");
        getTenDigitPhone(numbers->business);
    }
    else
    {
        numbers->business[0] = '\0';
    }
}


void getContact(struct Contact* contact)
{
    getName(&(contact->name));

    getAddress(&(contact->address));

    getNumbers(&(contact->numbers));
}
