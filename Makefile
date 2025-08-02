# compiler 
CC = gcc

# compiler flags
CFLAGS = -Wall -Wextra -g

# source code
SRC = main.c read_line.c parse_line.c launch_command.c run_command.c builtins.c handle_redirection.c pipeline.c

# build rule
mini_shell: $(SRC)
	$(CC) $(CFLAGS) -o mini_shell $(SRC)

# clean
clean:
	rm -f *.o mini_shell