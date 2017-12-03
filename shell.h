#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


char ** split_line(char* line, char* character, char* split_input, char ** retans);

void replace_str(char*line,char*substring,char*replace_with);

void execute(char** parsed_line);

void cd(char** parsed_line);

char** run_the_shell(char * command_input, char * input, char ** cmd);

void check_exit(char* token);

void print_dir();

int* locate_redirect(char **parsed_line );

void redirect(char **parsed_line);

int main();
