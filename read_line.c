#include "read_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// read line from stdin
char* read_line(void) {
  char* line = NULL;       // store line from user
  size_t buffer_size = 0;  // variable to hold size of line buffer

  // read line from stdin
  if (getline(&line, &buffer_size, stdin) == -1) {
    // if reading failed because reached end-of-file
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // exit shell successfully
    } else {
      // if reading failed because of some other error
      perror("readline");
      exit(EXIT_FAILURE);  // exit shell with error code
    }
  }
  return line;  // return input line
}