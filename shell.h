#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

char ** parse_args(char* line, char ** retans);
char ** split_line(char* line, char* character, char* split_input, char ** retans);
void execute(char** parsed_line);
char** parse_multiple_commands(char* line, char ** retans);
void replace_str(char*line,char*substring,char*replace_with);
char** run_the_shell(char * command_input, char * input, char ** cmd);
void print_dir();
void main();
