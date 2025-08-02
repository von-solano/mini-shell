#ifndef BUILTINS_H
#define BUILTINS_H

#define BOLD "\033[1;37m"
#define RED "\033[1;31m"
#define COLOUR_RESET "\033[0m"

// function declarations for builtin mini shell commands
int ms_cd(char** args);
int ms_help();
int ms_exit();

// external declarations
extern char *builtin_str[];
extern int (*builtin_func[])(char **);
int ms_num_builtins(void);

#endif