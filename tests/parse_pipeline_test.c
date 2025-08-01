// testing parse_pipeline functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function declarations
char* read_line(void);
char** parse_line(char* line);
char*** parse_pipeline(char* line);

int main() {
  // get user input
  printf("Please enter a pipeline (or press CTRL+D): \n");
  char* line = read_line();               // store line
  char*** tokens = parse_pipeline(line);  // parse pipeline

  // display piped commands
  for(int i = 0; tokens[i] != NULL; i++){
    printf("Command %d:\n", i+1);
    for(int j = 0; tokens[i][j] != NULL; j++){
        printf("Arg %d: %s\n", j, tokens[i][j]);
    }
  }

  // cleanup memory
  free(line);
  for (int i = 0; tokens[i] != NULL; i++) {
    for(int j = 0; tokens[i][j] != NULL; j++){
        free(tokens[i][j]);
    }
    free(tokens[i]);
  }
  free(tokens);

  return 0;
}