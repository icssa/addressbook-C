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
 * DATE: Oct 19, 2015
 *
 * FILE: database.c
 *
 * DESCRIPTION: This file contains the user database functions.
 *
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
extern int debugmode;

/*****************************************************************
 *
 * Function name: addRecord
 *
 * DESCRIPTION: Adds a record to the end of the database. Allows duplicates.
 *
 * Parameters: start (record **) : Pointer to array of records; start of our database.
 * name (char *) : Name of person to be added.
 * address (char *) : Address of person to be added.
 * yearofbirth (int) : Year of birth of person to be added.
 * telno (char *) : Telephone number of person to be added.
 * 
 * Return values: 1: success
 *
 *****************************************************************/
int addRecord(struct record **start, char name[], char address[], int yearofbirth, char telno[]) {

    struct record *data;
    struct record *temp;
    data = (struct record *) malloc(sizeof (struct record));


    if (debugmode == 1) {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: addRecord\n");
        printf("~PARAMS:\n");
        printf("~RECORD: start\n");
        printf("~NAME: %s\n", name);
        printf("~ADDRESS: %s\n", address);
        printf("~YEAROFBIRTH: %d\n", yearofbirth);
        printf("~TELNO: %s\n", telno);

        fflush(stdout);
    }

    if ((*start)->name != NULL) {
        temp = (*start);
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = data;

    } else {
        *start = data;
    }

    strcpy(data->name, name);
    strcpy(data->address, address);
    data->yearofbirth = yearofbirth;
    strcpy(data->telno, telno);
    data->next = NULL;

    return 1;
}

/*****************************************************************
 *
 * Function name: printRecord
 *
 * DESCRIPTION: Prints all records that correspond to the given name.
 * 
 * Parameters: start (record **) : Pointer to array of records; start of our database.
 * name (char *) : Name of person to be printed.
 *
 * Return values: 1 : success
 *  0 : failure
 *
 *****************************************************************/
int printRecord(struct record **start, char name[]) {
    struct record *temp = *start;
    if (debugmode == 1) {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: printRecord\n");
        printf("~PARAMS:\n\n");
        printf("~RECORD: start\n");
        printf("~NAME: %s\n", name);
        fflush(stdout);
    }

    if ((*start) != NULL) {

        while (temp != NULL) {
            if (strcmp((temp)->name, name) == 0) {
                printf("Name: %s\nAddress: %s\nBirth Year: %d\nPhone #: %s\n\n", temp->name, temp->address, temp->yearofbirth, temp->telno);
                fflush(stdout);
            }
            if (temp->next != NULL) {
                temp = temp->next;
            } else if (temp->next == NULL) {
                break;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

/*****************************************************************
 *
 * Function name: modifyRecord
 *
 * DESCRIPTION: Modifies all records that match the given name.
 *
 * Parameters: start (record **) : Pointer to array of records; start of our database.
 * name (char *) : Name of persons to be modified.
 * address (char *) : Address to modify to.
 * telno (char *) : Telephone number to modify to.
 * 
 * Return values: 1 : success
 *  0 : failure
 *
 *****************************************************************/
int modifyRecord(struct record **start, char name[], char address[], char telno[]) {

    struct record *temp = *start;
    if (debugmode == 1) {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: modifyRecord\n");
        printf("~PARAMS:\n\n");
        printf("~RECORD: start\n");
        printf("~NAME: %s\n", name);
        printf("~ADDRESS: %s\n", address);
        printf("~TELNO: %s\n", telno);

        fflush(stdout);
    }

    if ((*start) != NULL) {
        while (temp != NULL) {
            if (strcmp((temp)->name, name) == 0) {

                strcpy(temp->address, address);
                strcpy(temp->telno, telno);
            }
            if (temp->next != NULL) {
                temp = temp->next;
            } else if (temp->next == NULL) {
                break;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

/*****************************************************************
 *
 * Function name: printAllRecords
 *
 * DESCRIPTION: Prints all records.
 *
 * Parameters: start (record **) : Pointer to array of records; start of our database.
 * 
 * Return values: None.
 *
 *****************************************************************/
void printAllRecords(struct record **start) {
    struct record *temp;
    temp = *start;

    if (debugmode == 1) {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: printAllRecords\n");
        printf("~PARAMS:\n");
        printf("~RECORD: start\n");
        fflush(stdout);
    }
    
    if ((*start) != NULL) {
        do {
            printf("Name: %s\nAddress: %s\nBirth Year: %d\nPhone #: %s\n\n", temp->name, temp->address, temp->yearofbirth, temp->telno);
            if (temp->next == NULL) {
                break;
            }
            temp = temp->next;
        } while (temp != NULL);
    }
}

/*****************************************************************
 *
 * Function name: deleteRecord
 *
 * DESCRIPTION: Deletes all records that match the given name.
 *
 *  * Parameters: start (record **) : Pointer to array of records; start of our database.
 * name (char *) : Name of persons to be deleted.
 * 
 * Return values: 1 : success
 *  0 : failure
 *
 *****************************************************************/
int deleteRecord(struct record **start, char name[]) {


    struct record *temp = *start;
    struct record *temp2;

    if (debugmode == 1) {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: deleteRecord\n");
        printf("~PARAMS:\n");
        printf("~RECORD: start\n");
        printf("~NAME: %s\n", name);

        fflush(stdout);
    }

    if ((*start) != NULL) {
        while (strcmp((*start)->name, name) == 0) {
            *start = (*start)->next;
            free(temp);
            temp = (*start);

            if (temp == NULL) {
                break;
            }
        }

        temp2 = temp;

        while (temp != NULL) {
            if (strcmp(temp->name, name) == 0) {
                if (temp->next == NULL) {
                    temp2->next = NULL;
                    free(temp);
                    break;
                } else {
                    temp2->next = temp->next;
                    free(temp);
                    temp = temp2;
                }
            } else {
                temp2 = temp;
            }

            temp = temp->next;
        }
        return 1;
    } else {
        return 0;
    }
}

/*****************************************************************
 *
 * Function name: readfile
 *
 * DESCRIPTION: Opens a file from given filename. 
 * Copies the information in file into the records in memory.
 * 
 * Parameters: start (record **) : Pointer to array of records; start of our database.
 * filename (char *) : Name of txt file to open that contains our database.
 *
 * Return values: -1 : the file could not be found
 * 1 : success
 *
 *****************************************************************/
int readfile(struct record **start, char filename[]) {
    FILE *infile = fopen(filename, "r");

    char tempstring[100];
    char tempstring2[200];
    int templength = 0;

    struct record *data;
    struct record *temp;
    struct record *temp2;
    char name[25];
    char address[80];
    int yearofbirth;
    char telno[15];

    int manual = 1;
    int check = 0;

    if (debugmode == 1) {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: readfile\n");
        printf("~PARAMS:\n");
        printf("~RECORD: start\n");
        printf("~FILENAME: %s\n", filename);

        fflush(stdout);
    }

    if (infile == NULL) {
        return -1;
    }
    data = (struct record *) malloc(sizeof (struct record));

    *start = data;
    temp = (*start);
    tempstring2[0] = '\0';
    while (fgets(tempstring, sizeof (tempstring), infile) != NULL) {

        strcat(tempstring2, tempstring);
        templength = strlen(tempstring2);

        if (tempstring2[templength - 1] == '*') {
            templength++;
        }
        if (templength > 0 && tempstring2[templength - 2] == '*') {
            if (check == 0) {
                tempstring2[templength - 2] = '\0';
                strcpy(name, tempstring2);
                strcpy(data->name, name);
                tempstring2[0] = '\0';

                check++;
            } else if (check == 1) {
                tempstring2[templength - 2] = '\0';
                strcpy(address, tempstring2);
                strcpy(data->address, address);
                tempstring2[0] = '\0';

                check++;
            } else if (check == 2) {
                yearofbirth = atoi(tempstring2);
                data->yearofbirth = yearofbirth;
                tempstring2[0] = '\0';

                check++;
            } else if (check == 3) {
                tempstring2[templength - 2] = '\0';
                strcpy(telno, tempstring2);
                strcpy(data->telno, telno);
                tempstring2[0] = '\0';

                check++;
            }
            if (check == 4) {
                check = 0;

                temp->next = (struct record *) malloc(sizeof (struct record));
                temp2 = temp;
                data = temp->next;
                temp = temp->next;
                manual = 0;
            }
        }
    }

    free(temp);
    temp2->next = NULL;
    fclose(infile);
    return 1;
}

/*****************************************************************
 *
 * Function name: writefile
 *
 * DESCRIPTION: Writes a file to given filename. 
 * Copies the information in records in memory into the file.
 * 
 * Parameters: start (record **) : Pointer to array of records; start of our database.
 * filename (char *) : Name of txt file to open that contains our database we will write to.
 *
 * Return values: 0 : no records found
 * 1 : success
 *
 *****************************************************************/
int writefile(struct record **start, char filename[]) {

    FILE *file;

    struct record *temp;
    file = fopen(filename, "w");
    temp = *start;

    if (debugmode == 1) {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: writefile\n");
        printf("~PARAMS:\n");
        printf("~RECORD: start\n");
        printf("~FILENAME: %s\n", filename);

        fflush(stdout);
    }

    if ((*start) != NULL) {
        do {
            fprintf(file, "%s*\n%s*\n%d*\n%s*\n", temp->name, temp->address, temp->yearofbirth, temp->telno);
            if (temp->next == NULL) {
                break;
            }
            temp = temp->next;
        } while (temp != NULL);
    } else {
        return 0;
    }
    fclose(file);
    return 1;
}

/*****************************************************************
 *
 * Function name: cleanup
 *
 * DESCRIPTION: Deletes all records, sets start to NULL.
 * 
 * Parameters: start (record**) : array of record pointers
 *
 * Return values: none
 *
 *****************************************************************/
void cleanup(struct record **start) {

    struct record *temp = *start;
    struct record *temp2;

    if (debugmode == 1) {
        printf("\n***...DEBUG MODE...***\n");
        printf("~METHOD: cleanup\n");
        printf("~PARAMS:\n");
        printf("~RECORD: start\n");

        fflush(stdout);
    }

    if ((*start) != NULL) {

        temp2 = temp;

        while (temp != NULL) {

            if (temp->next == NULL) {
                free(temp);
                temp = NULL;
                temp2 = NULL;
                *start = NULL;
                break;
            } else {
                temp2 = temp->next;
                free(temp);
                temp = temp2;
            }
        }
    }
}



