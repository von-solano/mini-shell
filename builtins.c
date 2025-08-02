#include <stdio.h>
#include <unistd.h>
#include "builtins.h"

// change directory
int ms_cd(char** args){
    if(args[1] == NULL){
        fprintf(stderr, RED "ms: " COLOUR_RESET "expected argument to \"cd\"\n"); // missing argument
    } else {
        if(chdir(args[1]) != 0){
            fprintf(stderr, RED "ms: " COLOUR_RESET "no such file or directory\n"); // no such file or directory
        }
    }
    return 1; // keep shell running
}

// get help message
int ms_help(){
    
    printf("\nVon's Mini Shell\n");
    printf("Type in commands and arguments, and press enter.\n");
    printf("The following are built in:\n");

    for(int i = 0; i < ms_num_builtins(); i++){
        printf(" %s\n", builtin_str[i]);
    }

    printf("Use the 'man' command for information about other commands!\n\n");
    return 1; // keep shell running
}

// exit shell
int ms_exit(){
    return 0; // signal to shell to stop
}


// list of builtin commands
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[])(char **) = {
    &ms_cd,
    &ms_help,
    &ms_exit
};

// return number of builtin commands
int ms_num_builtins(){
    return sizeof(builtin_str) / sizeof(char *);
}