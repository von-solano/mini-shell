#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "handle_redirection.h"

int launch_command(char** args){
    
    int status;
    char *input_file = NULL;
    char *output_file = NULL;

    // handling redirection
    handle_redirection(args, &input_file, &output_file);

    pid_t pid = fork(); // create new process

    if(pid < 0){
        // fork failed...
        perror("fork failed!");
        exit(EXIT_FAILURE);
    } else if (pid == 0){
        // in child process
        
        // redirect stdin 
        if(input_file){
            int fd_in = open(input_file, O_RDONLY); // open file for reading
            if(fd_in < 0){
                perror("open file for input failed!");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO); // replace stdin with file 
            close(fd_in); // close unused file descriptor
        }

        // redirect stdout 
        if(output_file){
            int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // open file for writing
            if(fd_out < 0){
                perror("open file for output failed!");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO); // replace stdout with file 
            close(fd_out); // close unused file descriptor
        }

        // terminate process and run command
        execvp(args[0], args);
        // execvp failed...
        perror("execvp failed!");
        exit(EXIT_FAILURE);
    } else {
        // parent process
        do {
            waitpid(pid, &status, WUNTRACED); // wait for child process to finish
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
        // loop exits normally or gets killed by signal
    }
    return 1;
}