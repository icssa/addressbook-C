/*****************************************************************
 *
 * NAME: Spencer Allen
 *
 * HOMEWORK: Project 1
 *
 * CLASS: ICS 212
 *
 * INSTRUCTOR: Ravi Narayan
 *
 * DATE: Oct 17, 2015
 *
 * FILE: main.c
 *
 * DESCRIPTION: This file contains the user interface and functions for Address Book.
 *
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void getAddress(char *, int);
int getYear();
void getTelNum(char *); 
void getName(char *); 

int debugmode = 0;

int main(int argc, char *argv[]) 
{
    int exitprogram = 0;
    char optionarray[50];
    int inputvaliditycheck = 0;

    struct record *start = NULL;
    char name[25];
    char address[80];
    int yearofbirth = 0;
    char telNumber[15];
    char arg[15];

    if (argc < 3)
    {
        if (argc == 2) 
        {
            strcpy(arg, argv[1]);
            if (strstr(arg, "debug"))
            {
                if (strlen(arg) < 7)
                {
                    debugmode = 1;
                } else 
                {
                    printf("%s: Incorrect argument type.\nUsage: %s [debug]\n", argv[0], argv[0]);
                    fflush(stdout);
                    return (EXIT_SUCCESS);
                }
            } else 
            {
                printf("%s: Incorrect argument type.\nUsage: %s [debug]\n", argv[0], argv[0]);
                fflush(stdout);
                return (EXIT_SUCCESS);
            }
        }
        printf("\nWelcome to Address Book! \n");
        fflush(stdout);
        readfile(&start, "test.txt");
        while (exitprogram < 1) 
        {
            printf("\nPlease select an option: \n");
            printf("    1. Add a new record to the database \n");
            printf("    2. Modify a record in the database using the name as the key \n");
            printf("    3. Print information about a record using the name as the key \n");
            printf("    4. Print all information in the database \n");
            printf("    5. Delete an existing record from the database using the name as a key \n");
            printf("    6. Clean up database by deleting all records. \n");
            printf("    7. Quit the program \n");
            fflush(stdout);

            inputvaliditycheck = 0;

            if (fgets(optionarray, 10, stdin))
            {
                /*Add */
                if (strstr(optionarray, "1") != NULL || strstr(optionarray, "Add") != NULL || strstr(optionarray, "add") != NULL)
                {
                    printf("Please enter the following information for the person you want to add:");
                    getName(name);
                    getAddress(address, sizeof (address) + 1);
                    yearofbirth = getYear();
                    getTelNum(telNumber);
                    addRecord(&start, name, address, yearofbirth, telNumber);
                }
                
                /*Modify */
                else if (strstr(optionarray, "2") != NULL || strstr(optionarray, "Modify") != NULL || strstr(optionarray, "modify") != NULL) 
                {
                    printf("Please enter the following information for the person you want to modify:");
                    getName(name);
                    getAddress(address, sizeof (address) + 1);
                    getTelNum(telNumber);
                    modifyRecord(&start, name, address, telNumber);
                }
                
                /*Print 1 */
                else if (strstr(optionarray, "3") != NULL || strstr(optionarray, "Print") != NULL || strstr(optionarray, "print") != NULL && strstr(optionarray, "Print All") == NULL && strstr(optionarray, "print all") == NULL)
                {
                    fseek(stdin, 0, SEEK_END);
                    printf("Please enter the name of the person whose info you want to print: \n");
                    fflush(stdout);
                    getName(name);
                    printRecord(&start, name);
                }
                
                /*Print All */
                else if (strstr(optionarray, "4") != NULL || strstr(optionarray, "Print All") != NULL || strstr(optionarray, "Print all") != NULL || strstr(optionarray, "print all") != NULL || strstr(optionarray, "print All") != NULL) 
                {
                    printAllRecords(&start);
                }
                
                /*Delete */
                else if (strstr(optionarray, "5") != NULL || strstr(optionarray, "Delete") != NULL || strstr(optionarray, "delete") != NULL) 
                {
                    fseek(stdin, 0, SEEK_END);
                    printf("Please enter the name of the person whose info you want to delete: \n");
                    fflush(stdout);
                    getName(name);
                    deleteRecord(&start, name);
                }
                
                /*Cleanup*/
                else if (strstr(optionarray, "6") != NULL || strstr(optionarray, "Cleanup") != NULL || strstr(optionarray, "cleanup") != NULL) 
                {
                    fseek(stdin, 0, SEEK_END);
                    printf("Cleaning up records... \n");
                    fflush(stdout);
                    cleanup(&start);
                }
                
                /*Quit */
                else if (strstr(optionarray, "7") != NULL || strstr(optionarray, "Quit") != NULL || strstr(optionarray, "quit") != NULL) 
                {
                    exitprogram++;
                }
                
                /*Bad input */
                else 
                {
                    fseek(stdin, 0, SEEK_END);
                    printf("Invalid selection. Type the number or name of the option you want.\n");
                    fflush(stdout);
                }
            }
        }
    } else 
    {
        printf("%s: Incorrect number of arguments.\nUsage: %s [debug]\n", argv[0], argv[0]);
        fflush(stdout);
        return (EXIT_SUCCESS);
    }
    writefile(&start, "test.txt");
    fflush(stdout);
    return (EXIT_SUCCESS);
}

/*****************************************************************
 *
 * Function name: getAddress
 *
 * DESCRIPTION: A function that prompts the user for their address, then gets their input for it.
 *
 * Parameters: address (char[]):  Pointer to address array in program so we can save the user's input.
 * length (int) : The length of the array so we don't overflow from user input.
 *
 * Return values: None.
 *
 *****************************************************************/
void getAddress(char address[], int length) 
{
    int i = 0;
    char charbuff;
    if (debugmode == 1) 
    {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: getAddress\n");
        printf("~PARAMS:\n");
        printf("~ADDRESS: %s\n", address);
        printf("~LENGTH: %d\n", length);
        fflush(stdout);
    }

    fseek(stdin, 0, SEEK_END);
    printf("\nEnter address:\n(Press * then enter/newline to stop)\n");
    fflush(stdout);
    
    while (i < length) 
    {
        charbuff = fgetc(stdin);
        if (charbuff == '*') 
        {
            break;
        } else 
        {
            address[i] = charbuff;
            i++;
            fflush(stdout);
        }
    }
    address[i] = '\0';
}

/*****************************************************************
 *
 * Function name: getYear
 *
 * DESCRIPTION: A function that prompts the user for their year of birth, then gets their input for it.
 *
 * Parameters: None.
 *
 * Return values: temp (int) : The temp int used to hold user's date of birth.
 *
 *****************************************************************/
int getYear() 
{
    int check = 0;
    int temp;
    if (debugmode == 1)
    {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: getYear\n");
        printf("~PARAMS:\n");
        printf("~NONE~\n");
        fflush(stdout);
    }
    
    printf("\nEnter year of birth: \n");
    fflush(stdout);
    fseek(stdin, 0, SEEK_END);
    
    while (check < 1)
    {
        if (scanf("%d", &temp) != 1) 
        {
            fseek(stdin, 0, SEEK_END);
        } else
        {
            check++;
            fflush(stdout);
        }
    }
    return temp;
}

/*****************************************************************
 *
 * Function name: getTelNum
 *
 * DESCRIPTION: A function that prompts the user for their telephone number, then gets their input for it.
 *
 * Parameters: telNumber (char[]):  Pointer to telNumber array in program so we can save the user's input.
 * 
 *
 * Return values: None.
 *
 *****************************************************************/
void getTelNum(char telNumber[]) 
{
    if (debugmode == 1) 
    {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: getTelNum\n");
        printf("~PARAMS:\n");
        printf("~TELNUMBER: %s\n", telNumber);
        fflush(stdout);
    }
    
    fseek(stdin, 0, SEEK_END);
    printf("\nEnter telephone number: \n");
    fflush(stdout);
    fgets(telNumber, 15, stdin);
    telNumber[strcspn(telNumber, "\r\n")] = '\0';
}

/*****************************************************************
 *
 * Function name: getTelNum
 *
 * DESCRIPTION: A function that prompts the user for their name, then gets their input for it.
 *
 * Parameters: name (char[]):  Pointer to name array in program so we can save the user's input.
 * 
 *
 * Return values: None.
 *
 *****************************************************************/
void getName(char name[]) 
{
    if (debugmode == 1) 
    {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: getName\n");
        printf("~PARAMS:\n");
        printf("~NAME: %s\n", name);
        fflush(stdout);
    }

    fseek(stdin, 0, SEEK_END);
    printf("\nEnter name: \n");
    fflush(stdout);
    fgets(name, 25, stdin);
    name[strcspn(name, "\r\n")] = '\0';


}












