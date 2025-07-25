// testing launch_command function

#include <stdio.h>
#include <stdlib.h>

// function declarations
char* read_line(void);
char** parse_line(char* line);
int launch_command(char** args);
void handle_redirection(char **args, char **input_file, char **output_file);

int main() {
  // get user input
  printf("Please enter a line (or press CTRL+D): \n");
  char* line = read_line();        // store line
  char** args = parse_line(line);  // parse line into tokens

  // execute command
  if (args[0] != NULL) {
    launch_command(args);
  }

  // cleanup memory
  free(line);
  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);
  }
  free(args);

  return 0;
}