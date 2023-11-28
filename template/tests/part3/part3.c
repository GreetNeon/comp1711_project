#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    char steps[8];
} Fitness_Data;

Fitness_Data* read_from_file(char *file_loc){
    //Defining a file to get the row count
    FILE* count_file = fopen(file_loc, "r"); 
    //if the file doesn't exist output error message and return to main()

    //Defining a file to retrieve entries from
    FILE* input_file = fopen(file_loc, "r");
    //Using get_row_count to assign the amount of rows to a variable
    int row_count = get_row_count(count_file), count = 0;
    //Defining Buffer Arrays
    char buffer[30], prev_buffer[30];
    //Defining an entry, and an entries pointer
    Fitness_Data entry, *entries;
    //Allocating the appropriate amount of memory at the entries pointer
    entries = malloc(row_count * sizeof(Fitness_Data));
    //Looping Through the csv file
    while (fgets(buffer, sizeof(buffer), input_file))
    {
        //Tokenising each record into an entry
        tokeniseRecord(buffer, ",", entry.date, entry.time, entry.steps);
        //Assigning the entry to a memory location within entries
        entries[count] = entry;
        //Indexing the count
        count ++;
    }
    //closing the file after all entries have been retrieved
    fclose(input_file);
    return entries;
}

void validate_time(char time[]){
    char hour[3], minutes[3];
    char *p = time;
    const char *const_time = p;
    tokenise_time(const_time, ":", hour, minutes);
    printf("Hours: %s, minutes: %s\n", hour, minutes);
    return;
}

void main(){
    char file_path[1000];
    int running = 1;
    Fitness_Data *FitData;
    while(running == 1){
        printf("Enter Filename: ");
        scanf("%s", file_path);
        if (fopen(file_path, "r") == NULL){
            printf("Invalid File. Try Again\n");
        }
        else{
            printf("The file was successfully opened!\n");
            FitData = read_from_file(file_path);
            validate_time(FitData[0].time);
        }
    }
}

