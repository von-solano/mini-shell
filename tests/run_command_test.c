// testing run_command function

#include <stdio.h>
#include <stdlib.h>

// function declarations
char* read_line(void);
char** parse_line(char* line);
int run_command(char** args);

int main() {
  // get user input
  printf("Please enter a line (or press CTRL+D): \n");
  char* line = read_line();        // store line
  char** args = parse_line(line);  // parse line into tokens

  // run command
  if (args[0] != NULL) {
    run_command(args);
  }

  // cleanup memory
  free(line);
  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);
  }
  free(args);

  return 0;
}