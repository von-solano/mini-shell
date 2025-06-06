// testing read_line function

#include <stdio.h>
#include <stdlib.h>

char *read_line(void); // function declaration

int main(){
    printf("Please enter a line (or press CTRL+D): \n"); // ask for user input

    char *line = read_line(); // call function and store line

    printf("You entered: %s", line); // display results
    free(line); // cleanup memory

    return 0;
}