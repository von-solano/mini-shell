// testing parse_line function

#include <stdio.h>
#include <stdlib.h>

 // function declarations
char *read_line(void);
char** parse_line(char* line);

int main(){
    // get user input
    printf("Please enter a line (or press CTRL+D): \n"); 
    char *line = read_line(); // store line

    char **tokens = parse_line(line); // parse line into tokens
    int index = 0; // track index

    while(tokens[index] != NULL){
        printf("Token %d: %s \n", index+1, tokens[index]);
        index++;
    }

    // cleanup memory
    free(line);
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);

    return 0;
}