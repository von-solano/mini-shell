#include <stdio.h>
#include <string.h>
#include "run_command.h"
#include "launch_command.h"
#include "builtins.h"

int run_command(char** args){
    
    // no command was entered
    if(args[0] == NULL){
        return 1;
    }

    // check if command entered is a builtin and run
    for(int i = 0; i < ms_num_builtins(); i++){
        if(strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }

    // call launch to launch a process
    return launch_command(args);
}
