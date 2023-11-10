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

void output_row_count(char *file_path){
    FILE* counting_file = fopen(file_path, "r");
    int row_count = get_row_count(counting_file);
    printf("Row count of inputted file: %d\n", row_count);
    return;
}

Fitness_Data* read_from_file(char *file_loc){
    //Defining a File to be counted and a file to be formatted
    FILE* count_file = fopen(file_loc, "r"); 
    if (count_file == NULL){
        printf("File path invalid, Please enter a valid file path");
        return 0;
    }
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
    fclose(input_file);
    return entries;
}

void find_steps(char *file_path, Fitness_Data *entries, int *lowest, int *highest){
    FILE* count_file = fopen(file_path, "r");
    int i = 0, row_count = get_row_count(count_file), current_steps;
    while(i != row_count){
        current_steps = atoi(entries[i].steps);
        if(i == 0){
            *highest = current_steps;
            *lowest = current_steps;
        }
        else if(current_steps < *lowest){
            *lowest = current_steps;
        }
        if(current_steps > *highest){
            *highest = current_steps;
        }
        i ++;
    }
    return;
    


}

void main(){
    //Main function to create menu and take input
    char choice, buffer[1248], file_path[1248], high_low_steps[3];
    int string_len, lowest_steps, highest_steps;
    int running = 1;
    Fitness_Data *all_data;
    printf("This is a File Handling System\n\n");
    while(running == 1){
        printf("\nOptions:\n A-Input filename\n B-Display number of records\n C-Date with lowest steps\n D-Date with highest steps\n E-Mean step count\n F-Longest Period of steps above 500\n\nPlease select one of the options above: ");
        scanf("%s", buffer);
        //Entry validation to ensure a valid option is chosen
        //while (running == 1){
        while (find_str_len(buffer) != 1 || 97 > convert_to_ascii(tolower(buffer[0])) || 102 < convert_to_ascii(tolower(buffer[0]))){
            printf("\nPlease select a valid option (Single Character Format 'a'): ");
            scanf("%s", buffer);        
        }
        choice = tolower(buffer[0]);
        switch(choice){
            case 'a':
                printf("Please enter the file path: ");
                scanf("%s", file_path);
                file_path[strcspn(file_path, "\r\n")] = 0;
                printf("This is the file path u have inputted: %s\n", file_path);
                all_data = read_from_file(file_path);
                break;

            case 'b':
                if(strcmp(file_path, "") == 0){
                    printf("%s\n", file_path);
                    printf("Please input a file path first\n");
                    break;
                }
                else{
                    output_row_count(file_path);
                    break;
                }
            case 'c':
                find_steps(file_path, all_data, &lowest_steps, &highest_steps);
                printf("The lowest number of steps: %d", lowest_steps);
                break;
            
            case 'd':
                find_steps(file_path, all_data, &lowest_steps, &highest_steps);
                printf("The Highest number of steps: %d", highest_steps);
                break;

        }
        
    }
    return;
}