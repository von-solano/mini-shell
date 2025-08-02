#ifndef PIPELINE_H
#define PIPELINE_H

// parsing commands in pipeline
char ***parse_pipeline(char *line);

// execute commands in pipeline
int execute_pipeline(char ***commands);

#endif