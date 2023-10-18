#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    char date[11];
    char time[6];
    char steps[10];
} Fitness_Data;

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
//int get_num_of_rows(FILE *input_file){
    //int count = 0;
    //char row_buffer[30];
    //while(feof(input_file) == 0){
        //fgets(row_buffer, sizeof(row_buffer), input_file);
        //count++;
    //}
    //return count - 1;
//}


void read_from_file(FILE *input_file){
    char buffer[30];
    Fitness_Data entry;
    int row_count = 0;
    char prev_buffer[30];
    //int row_count = get_num_of_rows(input_file);
    while (feof(input_file) == 0)
    {
    fgets(buffer, sizeof(buffer), input_file);
    if (strcmp(prev_buffer, buffer) != 0){
        tokeniseRecord(buffer, ",", entry.date, entry.time, entry.steps);
        printf("Date: %s ", entry.date);
        printf("Time: %s ", entry.time);
        printf("Steps: %d\n", atoi(entry.steps));
        strcpy(prev_buffer, buffer);
        row_count++;
    }
    }
    printf("Number of records in file: %d\n", row_count);
    
    return;
}

void main(){
    FILE* data_stream = fopen("/workspaces/comp1711_project/data/FitnessData_2023.csv","r");
    if (data_stream == NULL){
        printf("Error opening file!\n");
    }
    else{
        printf("File opened successfully!\n");
    }
    read_from_file(data_stream);
    return;

}