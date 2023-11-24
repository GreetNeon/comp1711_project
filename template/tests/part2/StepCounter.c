#include "FitnessDataStruct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

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
    printf("Total records: %d\n", row_count);
    return;
}

//Creating a function to return the fitness_data struct once the filename has been inputted
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
//Defining a function to find the lowest and highest amount of steps
void find_steps(char *file_path, Fitness_Data *entries, int *lowest_count, int *highest_count){
    //Defining a file to e used to retrieve the row count
    FILE* count_file = fopen(file_path, "r");
    //Defining an i variable to be used in the while loop
    //Defining a row count variable to know when to terminate the while loop
    //Current steps, highest, and lowest will be used to store the steps and be compared to each other
    int i = 0, row_count = get_row_count(count_file), current_steps, highest, lowest;
    while(i != row_count){
        //get the current steps, according to the value of i
        current_steps = atoi(entries[i].steps);
        if(i == 0){
            //Setting the values of highest and lowest at the start of the loop
            highest = current_steps;
            lowest = current_steps;
        }
        //If current steps are lower than the lowest amount of steps so far
        else if(current_steps < lowest){
            //Set lowest = current steps
            lowest = current_steps;
            //set the lowest count to the current value of i, this gives the index of the lowest steps
            *lowest_count = i;
        }
        //If current steps is higher than the highest amount of steps stored
        if(current_steps > highest){
            //Set highest =  current_steps
            highest = current_steps;
            //Set highest_count variable which is passed in by refference to the current i, which gives
            //the index of the current highest steps
            *highest_count = i;
        }
        //increment i
        i ++;
    }
    return;
    
}
//Function to round a float into an int
int roundfloat(float num){
    //Declaring an int type of the entered float
    int int_num = (int)num;
    //If the decimal of the float is greater than 0.5
    if (num - int_num > 0.5){
        //return rounded up number
        return (int_num + 1);
    }
    else{
        //return rounded down number
        return int_num;
    }
}
//Creating a function to retur the mean of type float
int mean(Fitness_Data* entry_data, char *filepath){
    //Getting the row count, defining a count variable
    int row_count = get_row_count(fopen(filepath, "r")), count;
    //Defining a variable for the mean to be stored in of type float, and a total to be used to store the sum of the steps
    float mean, total = 0;
    //Looping through the Fitness_Data struct array
    for (count=0;count<row_count;count++){
        //Adding up all the steps
        total += atoi(entry_data[count].steps);
    }
    //Calculating the mean
    mean = (total/(float)row_count);
    return roundfloat(mean);
}
//Creating a function to find the longest period of steps above 500
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
                *start_period = count - (length);
                *end_period = count - 1;
            }
            is_period = 0;
            temp_length = 0;
        }
    }
}
void output_menu(){
    printf("Menu Options:\nA: Specify the filename to be imported\nB: Display the total number of records in the file\nC: Find the date and time of the timeslot with the fewest steps\nD: Find the date and time of the timeslot with the largest number of steps\nE: Find the mean step count of all the records in the file\nF: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\nEnter choice: ");
    return;
}

int main(int argc, char *argv[]){
    //Main function to create menu and take input
    char choice, buffer[1248], file_path[1248], high_low_steps[3];
    int string_len, lowest_steps, highest_steps, lowest_steps_count, highest_steps_count, start_period, end_period;
    int running = 1, entered = 0;
    Fitness_Data *all_data;
    int opt;
    if (argc == 1){
        strcpy(file_path, "../../FitnessData_2023.csv");
    }
    else{
        while ((opt = getopt(argc, argv, "f:")) != -1){
            switch(opt){
                case 'f': strcpy(file_path, optarg);
                entered = 1;
                all_data = read_from_file(file_path);
                break;
                default: strcpy(file_path, "../../FitnessData_2023.csv");
                break;
            }
        }
    }
    
    while(running == 1){
        output_menu();
        scanf("%s", buffer);
        //Entry validation to ensure a valid option is chosen
        while (find_str_len(buffer) != 1 || 97 > convert_to_ascii(tolower(buffer[0])) || 102 < convert_to_ascii(tolower(buffer[0]))){
            if (tolower(buffer[0]) == 'q'){
                break;
            }
            printf("Invalid choice. Try again.\n");
            output_menu();
            scanf("%s", buffer);        
        }
        choice = tolower(buffer[0]);
        switch(choice){
            case 'a':
                printf("Input filename: ");
                scanf("%s", file_path);
                file_path[strcspn(file_path, "\r\n")] = 0;
                if (fopen(file_path, "r") == NULL){
                    printf("Error: Could not find or open the file.\n");
                    return 1;
                }
                else{
                    printf("File successfully loaded.\n");
                    all_data = read_from_file(file_path);
                    entered = 1;
                }
                break;

            case 'b':
                if(entered == 0){
                    printf("Please input a file path first\n");
                    break;
                }
                else{
                    output_row_count(file_path);
                    break;
                }
            case 'c':
                if(entered == 0){
                    printf("Please input a file path first\n");
                    break;
                }
                else{
                    find_steps(file_path, all_data, &lowest_steps_count, &highest_steps_count);
                    printf("Fewest steps: %s %s\n", all_data[lowest_steps_count].date, all_data[lowest_steps_count].time);
                    break;
                }
            
            case 'd':
                if(entered == 0){
                    printf("Please input a file path first\n");
                    break;
                }
                else{
                    find_steps(file_path, all_data, &lowest_steps_count, &highest_steps_count);
                    printf("Largest steps: %s %s\n", all_data[highest_steps_count].date, all_data[highest_steps_count].time);
                    break;
                }

            case 'e':
                if(entered == 0){
                    printf("Please input a file path first\n");
                    break;
                }
                else{
                    printf("Mean step count: %d\n", mean(all_data, file_path));
                }
                break;

            case 'f':
                if(entered == 0){
                    printf("Please input a file path first\n");
                    break;
                }
                else{
                    longest_period(all_data, file_path, &start_period, &end_period);
                    printf("Longest period start: %s %s\nLongest period end: %s %s\n", all_data[start_period].date, all_data[start_period].time, all_data[end_period].date, all_data[end_period].time);
                    break;
                }

            case 'q':
                running = 0;
                free(all_data);
                return 1;
                break;


        }
        
    }
    return 1;
}