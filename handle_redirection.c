#include <stdio.h>
#include <string.h>
#include "handle_redirection.h"

// scanning for redirection
int handle_redirection(char **args, char **input_file, char **output_file){
  for (int i = 0; args[i] != NULL; i++) {

    // check for input or output file in redirection
    if((strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0) && args[i + 1] == NULL){
      fprintf(stderr, "ms: syntax error near unexpected token '%s'\n", args[i]);
      return 0;
    }
    
    // check for stdin redirection
    if (strcmp(args[i], "<") == 0 && args[i + 1] != NULL) {
      *input_file = args[i + 1]; // stores input file
      args[i] = NULL;
      args[i + 1] = NULL;
      i++; // increment
    } 
    // check for stdout redirection
    else if (strcmp(args[i], ">") == 0 && args[i + 1] != NULL) {
      *output_file = args[i + 1]; // stores output file
      args[i] = NULL;
      args[i + 1] = NULL;
      i++; // increment
    }
  }
  return 1;
}