#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parse_line.h"

#define PIPE_BUFFER_SIZE 8  // set initial pipe buffer size

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

    // parse command segment into parse_line function
    char **args = parse_line(segment);
    commands[num_cmds++] = args;

    // increase capacity if needed
    if (num_cmds >= capacity) {
      capacity += PIPE_BUFFER_SIZE;
      char ***new_commands = realloc(commands, capacity * sizeof(char **));
      if (!new_commands) {
        fprintf(stderr, "ms: memory allocation error\n");
        exit(EXIT_FAILURE);
      }
      commands = new_commands;
    }

    segment = strtok(NULL, "|");  // get next command
  }
  commands[num_cmds] = NULL;  // terminate commands array
  return commands;
}
