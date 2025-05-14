#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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