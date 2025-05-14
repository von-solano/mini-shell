#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_line.h"

#define BUFFER_SIZE 64          // set initial buffer size    
#define DELIMITERS " \t\r\n\a"   // delimiters to split arguments from input line

// take line and split into tokens
char **parse_line(char* line){
    int bufsize = BUFFER_SIZE; // starting buffer size of tokens array
    int index = 0; // current position in tokens array
    char** tokens = malloc(bufsize * sizeof(char*)); // array of tokens

    // check if memory allocation failed
    if(!tokens){
        fprintf(stderr, "ms: allocation error\n");
        exit(1); // exit shell successfully
    }

    char* token = strtok(line, DELIMITERS); // get first token

    // loop through line and extract tokens
    while(token != NULL){
        tokens[index] = token; // store current token in token array
        index++; // increment position in token array

        // if token array is full
        if(index >= bufsize){
            bufsize += BUFFER_SIZE;  // double size of buffer
            tokens = realloc(tokens, bufsize * sizeof(char*)); // reallocate memory to increase space
            
            // check if reallocation failed
            if(!tokens){
            fprintf(stderr, "ms: allocation error\n");
            exit(1); // exit shell successfully
            }
        }

        token = strtok(NULL, DELIMITERS); // get next token
    }

    tokens[index] = NULL; // terminate tokens array
    return tokens; // return array of tokens
}