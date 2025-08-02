#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtins.h"
#include "handle_redirection.h"
#include "launch_command.h"
#include "parse_line.h"
#include "pipeline.h"
#include "read_line.h"
#include "run_command.h"

// function to print mini shell prompt with colour
void print_prompt() { printf("\033[1;34mmini_shell>\033[0m "); }

// loop structure for mini shell
void ms_loop(void) {
  char* line;
  char** args = NULL;
  char*** pipeline = NULL;
  int status;

  // do while-loop (check status variable after)
  do {
    print_prompt();
    line = read_line(); // read in line from user

    // check if line contains pipe
    if(strchr(line, '|') != NULL){
      pipeline = parse_pipeline(line);
      if(pipeline){
        execute_pipeline(pipeline);
      } else {
        status = 1; // keep shell running if failed
      }
    } else {
      // else no pipes detected
      args = parse_line(line);     // split line into command and arguments
      status = run_command(args);  // execute command  
    }

    // cleanup
    free(line);
    if (args) {
      for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
      }
      free(args);
      args = NULL;
    }

    if(pipeline){
      free_pipeline(pipeline);
      pipeline = NULL;
    }

  } while (status);  // loop until status is 0
}

// main function
int main() {
  printf("\nWelcome to Von's Mini Shell! Type 'help' to get started!\n");
  // run mini shell loop
  ms_loop();
  printf("Mini-Shell Exiting. Goodbye!\n\n");
  return 0;
}