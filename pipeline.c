#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parse_line.h"
#include "pipeline.h"

#define PIPE_BUFFER_SIZE 8  // set initial pipe buffer size

// free commands in pipeline
void free_pipeline(char ***tokens){
  if(!tokens) return; // empty
  
  // clean up memory
  for (int i = 0; tokens[i] != NULL; i++) {
    for (int j = 0; tokens[i][j] != NULL; j++) {
      free(tokens[i][j]);
    }
    free(tokens[i]);
  }
  free(tokens);
}

// parse pipeline
char ***parse_pipeline(char *line) {
  int num_cmds = 0;
  int capacity = PIPE_BUFFER_SIZE;
  char ***commands = malloc(capacity * sizeof(char **));  // allocate command array

  // check if memory was allocated correctly
  if (!commands) {
    fprintf(stderr, "ms: memory allocation error\n");
    exit(EXIT_FAILURE);
  }

  // tokenise line by pipes '|'
  char *segment = strtok(line, "|");

  while (segment != NULL) {
    while (*segment == ' ') segment++;  // remove leading whitespaces

  if(*segment == '\0'){
    fprintf(stderr, "ms: syntax error: missing command near '|'\n");
    free_pipeline(commands);
    return NULL;
  }

    // parse command segment into parse_line function
    char **args = parse_line(segment);
    if(!args || !args[0]){
      fprintf(stderr, "ms: syntax error: missing command near '|'\n");
      free_pipeline(commands);
      return NULL;
    }

    commands[num_cmds++] = args;

    // increase capacity if needed
    if (num_cmds >= capacity) {
      capacity += PIPE_BUFFER_SIZE;
      char ***new_commands = realloc(commands, capacity * sizeof(char **));
      if (!new_commands) {
        fprintf(stderr, "ms: memory allocation error\n");
        free_pipeline(commands);
        exit(EXIT_FAILURE);
      }
      commands = new_commands;
    }

    segment = strtok(NULL, "|");  // get next command
  }
  commands[num_cmds] = NULL;  // terminate commands array
  return commands;
}



// execute commands in pipeline
int execute_pipeline(char ***commands){
  int i = 0;                // tracks current command index
  int in_fd = STDIN_FILENO; // holds input file descriptor for next command (initially stdin)
  int status;               // status of last child process

  // track process ids
  pid_t pid;
  pid_t last_pid = -1;
  
  // create array for pipe file descriptors
  int pipefd[2];

  // loop through commands (except last)
  while(commands[i + 1] != NULL){
    // create new pipe
    if(pipe(pipefd) == -1){
      fprintf(stderr, "ms: pipe creation error\n");
      exit(EXIT_FAILURE);
    }

    // fork child process
    pid = fork();
    if(pid < 0){
      // if fork failed
      fprintf(stderr, "ms: error forking process\n");
      exit(EXIT_FAILURE);
    } else if (pid == 0){
      // in child process
      // redirect stdin to input of previous command (or original stdin)
      if(dup2(in_fd, STDIN_FILENO) == -1){
        fprintf(stderr, "ms: dup2 input error\n");
        exit(EXIT_FAILURE);     
      }

      // redirect stdout to write end of current pipe
      if(dup2(pipefd[1], STDOUT_FILENO) == -1){
        fprintf(stderr, "ms: dup2 output error\n");
        exit(EXIT_FAILURE);     
      }

      // close unused file descriptors
      close(pipefd[0]); 
      close(pipefd[1]); 
      if(in_fd != STDIN_FILENO) close(in_fd);

      // execute command
      execvp(commands[i][0], commands[i]);
      fprintf(stderr, "ms: %s: command not found\n", commands[i][0]);
      exit(EXIT_FAILURE);
    }
    // in parent process
    close(pipefd[1]); // finished writing to pipe 
    if(in_fd != STDIN_FILENO) close(in_fd); // close previous reading end of pipe
    in_fd = pipefd[0]; // next command reads from current pipe's read end
    i++; // move to next command
  }
  // handling last pipe...

  // fork process for last command
  last_pid = fork();
  if(last_pid < 0){
    // if fork failed
    fprintf(stderr, "ms: error forking process\n");
    exit(EXIT_FAILURE);  
  } else if (last_pid == 0){
    // in child process
    if(dup2(in_fd, STDIN_FILENO) == -1){
      fprintf(stderr, "ms: dup2 input error (last)\n");
      exit(EXIT_FAILURE);     
    }

    if(in_fd != STDIN_FILENO) close(in_fd);
    
    // run commands
    execvp(commands[i][0], commands[i]);
    fprintf(stderr, "ms: %s: command not found\n", commands[i][0]);
    exit(EXIT_FAILURE);
  }
  // in parent process
  if(in_fd != STDIN_FILENO) close(in_fd);

  // wait for all child processes
  pid_t wpid;
  int last_status = 0;
  while((wpid = wait(&status)) > 0){
    if(wpid == last_pid){
      last_status = status; // record last command exit status
    }
  }

  // record exit status of last command
  return WIFEXITED(last_status) ? WEXITSTATUS(last_status) : 1;
}