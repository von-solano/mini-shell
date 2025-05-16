// entry point to mini shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "launch_command.h"
#include "parse_line.h"
#include "read_line.h"
#include "run_command.h"

// loop structure for mini shell
void ms_loop(void) {
  char* line;
  char** args;
  int status;

  // do while-loop (check status variable after)
  do {
    printf("mini_shell> ");
    line = read_line();          // read in line from user
    args = parse_line(line);     // split line into command and arguments
    status = run_command(args);  // execute command

    // free variables
    free(line);
    if (args) {
      free(args);
    }
  } while (status);  // loop until status is 0
}

// main function
int main(int argc, char** argv) {

  printf("Welcome to Von's Mini Shell! Type 'help' to get started!\n");  
  // run mini shell loop
  ms_loop();

  return 0;
}