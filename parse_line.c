#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_line.h"
#include "parse_line.h"


#define BUFFER_SIZE 64          // set initial buffer size
#define DELIMITERS " \t\r\n\a"  // delimiters to split arguments from input line

// parse line from stdin
char** parse_line(char* line) {
  int bufsize = BUFFER_SIZE;                        // starting buffer size of tokens array
  int index = 0;                                    // current position in tokens array
  char** tokens = malloc(bufsize * sizeof(char*));  // array of tokens

  // check if memory allocation failed
  if (!tokens) {
    fprintf(stderr, RED "ms: " COLOUR_RESET "memory allocation error\n");
    exit(EXIT_FAILURE);  // exit shell successfully
  }

  char* saveptr; // save state for strtok_r
  char* token = strtok_r(line, DELIMITERS, &saveptr);  // get first token

  // loop through line and extract tokens
  while (token != NULL) {
    tokens[index] = strdup(token);  // store copy of current token in token array
    index++;                        // increment position in token array

    // if token array is full
    if (index >= bufsize) {
      bufsize += BUFFER_SIZE;  // double size of buffer
      tokens = realloc(tokens, bufsize * sizeof(char*)); 

      // check if reallocation failed
      if (!tokens) {
        fprintf(stderr, RED "ms: " COLOUR_RESET "memory allocation error\n");
        exit(EXIT_FAILURE);  // exit shell successfully
      }
    }
    token = strtok_r(NULL, DELIMITERS, &saveptr);  // get next token
  }

  tokens[index] = NULL;  // terminate tokens array
  return tokens;         // return array of tokens
}