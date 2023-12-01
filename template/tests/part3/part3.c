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

int validate_time(char time[]){
    char hour[10], minutes[10];
    char *temp_p = time;
    const char *const_time = temp_p;
    tokenise_time(const_time, ":", hour, minutes);
    if(strcmp(hour, "") == 0 || strcmp(minutes, "") == 0){
        return 0;
    }
    else if((-1<atoi(hour) && atoi(hour)<24) && (-1<atoi(minutes) && atoi(minutes)<61)){
        printf("Hours:%s\n", hour);
        return 1;
    }
    else{
        return 0;
    }
}
int validate_date(char date[]){
    char year[10], month[10], day[10], *temp_p = date;
    const char *const_date = temp_p;
    tokeniseRecord(const_date, "-", year, month, day);
    if(strcmp(year, "") == 0 || strcmp(month, "") == 0 || strcmp(day, "") == 0){
        return 0;
    }
    int year_i = atoi(year), month_i = atoi(month), day_i = atoi(day);
    if((2000<year_i && year_i<3000) && (0<month_i && month_i<13) && (0<day_i && day_i<31)){
        return 1;
    }
    else{
        return 0;
    }

}
int validate_steps(char *steps){
    if(steps[0] == '\n'){
        return 0;
    }
    int steps_i = atoi(steps);
    if(-1<steps_i){
        return 1;
    }
    else{
        return 0;
    }
}

void create_tsv(char *file_path, Fitness_Data *data, int row_count){
    char *new_file_path = strcat(file_path, ".tsv");
    printf("%s", new_file_path);
    int i;
    FILE* new_file = fopen(new_file_path, "w");
    for(i=0; i<row_count;i++){
        data[i].date[strcspn(data[i].date, "\r\n")] = 0;
        data[i].time[strcspn(data[i].time, "\r\n")] = 0;
        data[i].steps[strcspn(data[i].steps, "\r\n")] = 0;
        fprintf(new_file, "%s\t%s\t%d\n", data[i].date, data[i].time, atoi(data[i].steps));
    }
}

void bubblesort(Fitness_Data *data, char *file_path, int row_count){
    int i, j;
    Fitness_Data temporary_data;

    for(i = 0; i<row_count; i++){
        for(j = 0; j<row_count-i;j++){
            if(atoi(data[j].steps) < atoi(data[j+1].steps)){
                temporary_data = data[j+1];
                data[j+1] = data[j];
                data[j] = temporary_data;
            }
        }
    }
}

int main(){
    char file_path[1000];
    int running = 1, row_count, index;
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
            row_count = get_row_count(fopen(file_path, "r"));
            printf("%d\n", validate_time(FitData[0].time));
            printf("%d\n", validate_date(FitData[0].date));
            printf("%d\n", validate_steps(FitData[0].steps));
            int date_valid, time_valid, steps_valid;
            for(index=0;index<row_count;index++){
                date_valid = validate_date(FitData[index].date);
                time_valid = validate_time(FitData[index].time);
                steps_valid = validate_steps(FitData[index].steps);
                if((date_valid == 0) || (time_valid == 0) || (steps_valid == 0)){
                    printf("Data invalid!\n");
                    return 0;
                }
                }
            printf("All data is valid\n");
            int row_count = get_row_count(fopen(file_path, "r"));
            bubblesort(FitData, file_path, row_count);
            printf("Lowest steps: %sHighest steps: %s\n", FitData[58].steps, FitData[0].steps);
            create_tsv(file_path, FitData, row_count);
            return 1;
            }
    }
}


