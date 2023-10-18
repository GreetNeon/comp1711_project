#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void read_from_file(FILE *input_file){
    char buffer[30];
    while (feof(input_file) != true)
    {
    fgets(buffer, sizeof(buffer), input_file);
    printf("%s", buffer);  
    }
    
    
    return;
}

void main(){
    typedef struct{
        char date[11];
        char time[6];
        int steps;
    } Fitness_Data;
    FILE* data_stream =fopen("/workspaces/comp1711_project/data/FitnessData_2023.csv","r");
    if (data_stream == NULL){
        printf("Error opening file!\n");
    }
    else{
        printf("File opened successfully!\n");
    }
    read_from_file(data_stream);
    return;

}