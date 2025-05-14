// testing read_line from main.c

#include <stdio.h>
#include <stdlib.h>

char *read_line(void); // function declaration

int main(){
    printf("Please enter a line (or press CTRL+D): \n"); // ask for user input

    char *line = read_line(); // call function and store line

    printf("You entered: %s\n", line); // display results
    free(line); // cleanup memory

    return 0;
}