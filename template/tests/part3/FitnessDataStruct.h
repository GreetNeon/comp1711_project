#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
int find_str_len(char *string){
    char *i;
    for (i = string;  *i; i++);
    return i - string;
}
int convert_to_ascii(char input_char){
    int ascii = input_char;
    return ascii;
}
void tokenise_time(const char *input, const char *delimiter,
                    char *hour, char *minutes) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(hour, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(minutes, token);
    }
    free(inputCopy);
}