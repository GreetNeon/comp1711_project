#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Defining the data structure used to store the tokens
typedef struct{
    char date[11];
    char time[6];
    char steps[10];
} Fitness_Data;

//Function to return the amount of rows in a file
int get_row_count(FILE* count_file){
    //Defining a buffer to be used in order to count the number of rows
    char count_buffer[30];
    //Initialising the row counter to 0
    int row_count = 0;
    //Looping through the csv file
    while (fgets(count_buffer, sizeof(count_buffer), count_file)){
        //indexing the row counter each loop
        row_count++;
    }
    //closing the count file
    fclose(count_file);

    return row_count;
}

void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

void read_from_file(char *file_loc){
    //Defining a File to be counted and a file to be formatted
    FILE* count_file = fopen(file_loc, "r"); 
    FILE* input_file = fopen(file_loc, "r");
    //Defining a count variable to add entries to the entries array
    //Using get_row_count to assign the amount of rows to a variable
    int row_count = get_row_count(count_file), count = 0;
    //Defining Buffer Arrays
    char buffer[30], prev_buffer[30];
    //Defining an entry, and an entries pointer
    Fitness_Data entry, *entries;
    //Allocating the appropriate amount of memory to entries
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
    //Printing the number of records in the file
    printf("Number of records in file: %d\n", row_count);
    //Printing the first 3 entries formatted
    printf("%s/%s/%s", entries[0].date, entries[0].time, entries[0].steps);
    printf("%s/%s/%s", entries[1].date, entries[1].time, entries[1].steps);
    printf("%s/%s/%s", entries[2].date, entries[2].time, entries[2].steps);
    
    
    return;
}

void main(){
    //running the read from file function with the assigned csv file
    read_from_file("/workspaces/comp1711_project/data/FitnessData_2023.csv");
    return;

}