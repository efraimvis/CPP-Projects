#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ADTStack.h"

#define MAX_LENGTH 16

typedef struct intl_passenger
{
 char given_name[MAX_LENGTH];
 char surname[MAX_LENGTH];
 char passport_id[MAX_LENGTH];
 char country[MAX_LENGTH];
}intl;

/*
*Deep copies struct members of given passenger to a new passenger
*
* passanger - given passenger
*
* return : Returns a new passenger with struct members copied from given passenger*/
void* cpy_passenger(void* passenger)
{
    if(passenger)
    {
        intl* new_passenger;
        new_passenger = (intl*)malloc(sizeof(intl));
        if(!new_passenger)
        {
            printf("\nError - could not allocate memory\n");
            return NULL;
        }
        strcpy(new_passenger->given_name,((intl*)passenger)->given_name);
        strcpy(new_passenger->surname, ((intl*)passenger)->surname);
        strcpy(new_passenger->passport_id, ((intl*)passenger)->passport_id);
        strcpy(new_passenger->country, ((intl*)passenger)->country);
        return (void*)new_passenger;
    }
    return NULL;
}

/*
*Frees memory allocated to passenger
*
* passenger - given passenger*/
void free_passenger(void* passenger)
{
    if(passenger)
    {
        free(((intl*)passenger)->given_name);
        free(((intl*)passenger)->surname);
        free(((intl*)passenger)->passport_id);
        free(((intl*)passenger)->country);

        free(passenger);
        passenger = NULL;
    }
}

/*
*Returns a string representing a passenger
*
* passenger - given passenger
*
* return : Returns a string representing a passenger*/
char* label_passenger(void* passenger)
{
    if(passenger)
    {
        char* label;
        label = (char*)calloc(48,1);
        if(!label) 
        {
            printf("\nError - could not allocate memory\n");
            return NULL;
        }
        label[47] = '\0';
        strcpy(label, ((intl*)passenger)->given_name);
        strcat(label, " ");
        strcat(label, ((intl*)passenger)->surname);
        strcat(label, " ");
        strcat(label, ((intl*)passenger)->passport_id);

        return label;
    }
    return NULL;
}

/*
*Reads from a file in given directory and generates a stack with 56 passengers from information in file
*
* directory - directory to file
*
* return : Returns a Stack with 56 passengers read from file*/
Stack read_file(const char* directory)
{
    FILE* file;
    int i;
    Stack stack;
    stack = init(56, cpy_passenger, free_passenger, label_passenger);
    if(!stack) return NULL;
    file = fopen(directory, "r");
    if(!file) return NULL;
    for(i=0;i<56;i++)
    {
        intl* passenger;
        char* buf;
        char* token;
        char space[2];
        size_t bufsize;
        passenger = (intl*)malloc(sizeof(intl));
        if(!passenger) return NULL;
        strcpy(space, " ");
        buf = NULL;
        bufsize = 0;
        getline(&buf, &bufsize, file);
        token = strtok(buf,space);
        strcpy(passenger->given_name,token);
        token = strtok(NULL, space);
        strcpy(passenger->surname, token);
        token = strtok(NULL, space);
        strcpy(passenger->passport_id, token);
        token = strtok(NULL,space);
        strcpy(passenger->country, token);
        push(stack, (void*)passenger);
        free(passenger);
        passenger = NULL;
    }
    fclose(file);
    return stack;
}

/*
*Generates a file in given directory with passenger information from given stack
*
* directory - directory to file
* stack - given stack
*
**/
void write_file(const char* directory, Stack stack)
{
    if(stack)
    {
        int i;
        FILE* file;
        file = fopen(directory, "w");
        if(!file) return;
        for(i=0;i<56;i++)
        {
            fprintf(stdout, label_passenger(pop(stack)));
            fprintf(stdout,"\n");
        }
        fclose(file);
    }
}

/*Runs program*/
int main(void)
{
    Stack stack;
    stack = init(56,cpy_passenger, free_passenger, label_passenger);
    stack = read_file("international_passengers.dat");
    write_file("file.txt",stack);
    return 0;
}