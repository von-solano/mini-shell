#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


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

// loop structure for mini shell
void mini_shell_loop(void){
    char* line;
    char **args;
    int status;

    // do while-loop (check status variable after)
    do {
        printf("mini_shell> ");
        line = read_line(); // read in line from user
        args = parse_line(); // split line into command and arguments
        status = run_command(args); // execute command

        // free variables
        free(line);
        free (args);
    } while(status); // loop until status is 0
}

// main function
int main(int argc, char**argv){

    // run mini shell loop
    mini_shell_loop();
    
    return 0;
}