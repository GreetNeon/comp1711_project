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

//Creating a function for option B outputing row count
void output_row_count(char *file_path){
    //Opening a file to be counted
    FILE* counting_file = fopen(file_path, "r");
    //calling a function in fitness_header.h to return the row count and close the counting file
    int row_count = get_row_count(counting_file);
    //Outputting the row count
    printf("Row count of inputted file: %d\n", row_count);
    return;
}

//Creating a function to return the fitness_data struct once the filename has been inputted
Fitness_Data* read_from_file(char *file_loc){
    //Defining a file to get the row count
    FILE* count_file = fopen(file_loc, "r"); 
    //if the file doesn't exist output error message and return to main()
    if (count_file == NULL){
        printf("File path invalid, Please enter a valid file path");
        return 0;
    }
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
//Defining a function to find the lowest and highest amount of steps
void find_steps(char *file_path, Fitness_Data *entries, int *lowest_count, int *highest_count){
    FILE* count_file = fopen(file_path, "r");
    int i = 0, row_count = get_row_count(count_file), current_steps, highest, lowest;
    while(i != row_count){
        current_steps = atoi(entries[i].steps);
        if(i == 0){
            highest = current_steps;
            lowest = current_steps;
        }
        else if(current_steps < lowest){
            lowest = current_steps;
            *lowest_count = i;
        }
        if(current_steps > highest){
            highest = current_steps;
            *highest_count = i;
        }
        i ++;
    }
    return;
    
}

float mean(Fitness_Data* entry_data, char *filepath){
    int row_count = get_row_count(fopen(filepath, "r")), count, total = 0;
    float mean;
    for (count=0;count<row_count;count++){
        total += atoi(entry_data[count].steps);
    }
    mean = total/row_count;
    return mean;
}

void longest_period(Fitness_Data* entry_date, char* filepath, int *start_period, int *end_period){
    int row_count = get_row_count(fopen(filepath, "r")), count, length=0, temp_length=0, is_period=0;
    for(count=0;count<row_count;count++){
        if (atoi(entry_date[count].steps) > 500 && is_period == 0){
            temp_length += 1;
            is_period = 1;
            
        }
        else if(atoi(entry_date[count].steps) > 500 && is_period == 1){
            temp_length += 1;

        }
        else if(atoi(entry_date[count].steps) <= 500 && is_period == 1){
            if (temp_length > length){
                length = temp_length;
                *start_period = count - (length-1);
                *end_period = count;
            }
            is_period = 0;
            temp_length = 0;
        }
    }
}

void main(){
    //Main function to create menu and take input
    char choice, buffer[1248], file_path[1248], high_low_steps[3];
    int string_len, lowest_steps, highest_steps, lowest_steps_count, highest_steps_count, start_period, end_period;
    int running = 1;
    Fitness_Data *all_data;
    printf("This is a File Handling System\n\n");
    while(running == 1){
        printf("\nOptions:\n A-Input filename\n B-Display number of records\n C-Date with lowest steps\n D-Date with highest steps\n E-Mean step count\n F-Longest Period of steps above 500\n\nPlease select one of the options above: ");
        scanf("%s", buffer);
        //Entry validation to ensure a valid option is chosen
        //while (running == 1){
        while (find_str_len(buffer) != 1 || 97 > convert_to_ascii(tolower(buffer[0])) || 102 < convert_to_ascii(tolower(buffer[0]))){
            if (tolower(buffer[0]) == 'q'){
                break;
            }
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
                find_steps(file_path, all_data, &lowest_steps_count, &highest_steps_count);
                printf("The lowest number of steps: %d on date: %s at time: %s\n", atoi(all_data[lowest_steps_count].steps), all_data[lowest_steps_count].date, all_data[lowest_steps_count].time);
                break;
            
            case 'd':
                find_steps(file_path, all_data, &lowest_steps_count, &highest_steps_count);
                printf("The Highest number of steps: %d on date: %s at time: %s\n", atoi(all_data[highest_steps_count].steps), all_data[highest_steps_count].date, all_data[highest_steps_count].time);
                break;

            case 'e':
                printf("The mean is: %f\n", mean(all_data, file_path));
                break;

            case 'f':
                longest_period(all_data, file_path, &start_period, &end_period);
                printf("Start date and time: %s@%s, end date and time: %s@%s\n", all_data[start_period].date, all_data[start_period].time, all_data[end_period].date, all_data[end_period].time);
                break;

            case 'q':
                running = 0;
                break;


        }
        
    }
    return;
}