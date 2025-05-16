#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int launch_command(char** args){

    pid_t pid, wpid; // initialise process id's
    int status;

    pid = fork(); // create new process

    if(pid < 0){
        // fork failed...
        perror("fork failed!");
        exit(EXIT_FAILURE);
    } else if (pid == 0){
        // in child process
        execvp(args[0], args); // terminate process and run command
        // execvp failed...
        perror("execvp failed!");
        exit(EXIT_FAILURE);
    } else {
        // parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED); // wait for child process to finish
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
        // loop exits normally or gets killed by signal
    }
    return 1;
}