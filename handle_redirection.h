#ifndef HANDLE_REDIRECTION_H
#define HANDLE_REDIRECTION_H

#define RED "\033[1;31m"
#define COLOUR_RESET "\033[0m"

// scanning for redirection
int handle_redirection(char **args, char **input_file, char **output_file);

#endif