#include "fitness_header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char date[11];
    char time[6];
    char steps[10];
} Fitness_Data;


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
    //Printing the first 3 entries formatted if there are 3 or more entries
    if (row_count >= 3){
        printf("%s/%s/%s", entries[0].date, entries[0].time, entries[0].steps);
        printf("%s/%s/%s", entries[1].date, entries[1].time, entries[1].steps);
        printf("%s/%s/%s", entries[2].date, entries[2].time, entries[2].steps);
    }
    
    return;
}

void main(){
    //Main function to create menu and take input
    char choice, buffer[1248];
    int string_len;
    printf("This is a File Handling System\n\nOptions:\n A-Input filename\n B-Display number of records\n C-Date with lowest steps\n D-Date with highest steps\n E-Mean step count\n F-Longest Period of steps above 500\n");
    printf("\nPlease select one of the options above: ");
    scanf("%s", buffer);
    while (find_str_len(buffer) != 1 || 97 > convert_to_ascii(tolower(buffer[0])) || 102 < convert_to_ascii(tolower(buffer[0]))){
        printf("\nPlease select a valid option (Single Character Format 'a'): ");
        scanf("%s", buffer);        
    }
    choice = tolower(buffer[0]);
    printf("%d\n", convert_to_ascii(buffer[0]));
    return;
}