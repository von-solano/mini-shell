#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "handle_redirection.h"
#include "launch_command.h"


// execute command
int launch_command(char **args) {
  int status;
  char *input_file = NULL;
  char *output_file = NULL;

  // handling redirection
  if(!handle_redirection(args, &input_file, &output_file)) return 1;

  pid_t pid = fork();  // create new process

  if (pid < 0) {
    // if fork failed
    fprintf(stderr, RED "ms: " COLOUR_RESET "error forking process\n");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    // in child process
    // redirect stdin if redirection detected
    if (input_file) {
      int fd_in = open(input_file, O_RDONLY);  // open file for reading
      if (fd_in < 0) {
        fprintf(stderr, RED "ms: " COLOUR_RESET "cannot open input file '%s': %s\n", input_file, strerror(errno));
        exit(EXIT_FAILURE);
      }
      dup2(fd_in, STDIN_FILENO);  // replace stdin with file
      close(fd_in);               // close unused file descriptor
    }

    // redirect stdout if redirection detected
    if (output_file) {
      int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);  // open file for writing
      if (fd_out < 0) {
        fprintf(stderr, RED "ms: " COLOUR_RESET "cannot open output file '%s': %s\n", output_file, strerror(errno));
        exit(EXIT_FAILURE);
      }
      dup2(fd_out, STDOUT_FILENO);  // replace stdout with file
      close(fd_out);                // close unused file descriptor
    }

    // terminate process and run command
    if (execvp(args[0], args) == -1) {
      // if command failed
      fprintf(stderr, RED "ms: " COLOUR_RESET "%s: command not found\n", args[0]);
      exit(EXIT_FAILURE);
    }

  } else {
    // parent process
    do {
      waitpid(pid, &status, WUNTRACED);  // wait for child process to finish
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    // loop exits normally or gets killed by signal
  }
  return 1;
}