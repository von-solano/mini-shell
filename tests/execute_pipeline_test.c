// testing execute_pipeline functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function declarations
char* read_line(void);
char** parse_line(char* line);
char*** parse_pipeline(char* line);
int execute_pipeline(char*** commands);

int main() {
  // get user input
  printf("Please enter a pipeline (or press CTRL+D): \n");
  char* line = read_line();               // store line
  char*** tokens = parse_pipeline(line);  // parse pipeline
  execute_pipeline(tokens);               // execute pipeline

  // cleanup memory
  free(line);
  for (int i = 0; tokens[i] != NULL; i++) {
    for (int j = 0; tokens[i][j] != NULL; j++) {
      free(tokens[i][j]);
    }
    free(tokens[i]);
  }
  free(tokens);

  return 0;
}