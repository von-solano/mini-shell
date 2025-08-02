#ifndef PIPELINE_H
#define PIPELINE_H

#define RED "\033[1;31m"
#define COLOUR_RESET "\033[0m"

// parsing commands in pipeline
char ***parse_pipeline(char *line);

// execute commands in pipeline
int execute_pipeline(char ***commands);

// free commands in pipeline
void free_pipeline(char ***tokens);

#endif