#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct{
    char date[11];
    char time[6];
    char steps[10];
} Fitness_Data;

// Define any additional variables here



// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
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


// Complete the main function
void main(char *file_path){
    //Defining a File to be counted and a file to be formatted
    FILE* count_file = fopen(file_path, "r"); 
    FILE* input_file = fopen(file_path, "r");
    //Defining a count variable to add entries to the entries array
    //Using get_row_count to assign the amount of rows to a variable
    int row_count = get_row_count(count_file), count = 0;
    //Defining Buffer Arrays
    char buffer[30], prev_buffer[30];
    //Defining an entry, and an entries pointer to create an array of type Fitness_Data
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
    //Printing the first 3 entries formatted if there are 3 or more entries
    if (row_count >= 3){
        printf("%s/%s/%s", entries[0].date, entries[0].time, entries[0].steps);
        printf("%s/%s/%s", entries[1].date, entries[1].time, entries[1].steps);
        printf("%s/%s/%s", entries[2].date, entries[2].time, entries[2].steps);
    }
    
    return;
}

