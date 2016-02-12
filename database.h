

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"



int addRecord(struct record **, char [], char [], int, char []);
int printRecord(struct record *, char []);
int modifyRecord(struct record *, char [], char [], char []);
void printAllRecords(struct record *);
int deleteRecord(struct record **, char []);
void cleanup(struct record **);
int readfile(struct record **, char []);
void writefile(struct record *, char []);


