#include <stdio.h>
#include <stdlib.h>
#include "read_line.h"

// reading in line from user
char *read_line(void){
    char* line = NULL;       // store line from user
    size_t buffer_size = 0; // variable to hold size of line buffer

    // read line from stdin
    if(getline(&line, &buffer_size, stdin) == -1){
        // if reading failed beacuse reached the end-of-file
        if(feof(stdin)){
            exit(0); // exit shell successfully
        } else {
            // if reading failed because of some other error
            perror("readline");
            exit(1); // exit shell with error code
        }
    }
    return line; // return input line
}