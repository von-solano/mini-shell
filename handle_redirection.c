#include <string.h>

// scanning for redirection
void handle_redirection(char **args, char **input_file, char **output_file){
  for (int i = 0; args[i] != NULL; i++) {
    
    // check for stdin redirection
    if (strcmp(args[i], "<") == 0 && args[i + 1] != NULL) {
      *input_file = args[i + 1]; // stores input file
      args[i] = NULL;
      args[i + 1] = NULL;

    // check for stdout redirection
    } else if (strcmp(args[i], ">") == 0 && args[i + 1] != NULL) {
      *output_file = args[i + 1]; // stores output file
      args[i] = NULL;
      args[i + 1] = NULL;
    }
  }
}