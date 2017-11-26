#include "shell.h"


// changes retans to contain the tokens of line as determined by character
char ** split_line(char* line, char* character, char* split_input, char ** retans) {
  int i=0;
  strcpy(split_input,line);
  char *input_pointer = split_input;
  while (retans[i] = strsep(&input_pointer, character)) {
    i++;
  }
  //retans[i] = 0; // NULL termination
  return retans;
}

// this is for if the user types ls ; ls; ls ;ls (space differences)
void replace_str(char* line, char* substring, char* replace_with){
  char buffer[100];
  char*p=line;
  while((p=strstr(p,substring))){
    strncpy(buffer, line, p-line);
    buffer[p-line]='\0';
    strcat(buffer,replace_with);
    strcat(buffer,p+strlen(substring));
    strcpy(line,buffer);
    p++;
  }
}

void execute(char **parsed_line) {
  //printf("@@%s\n", parsed_line[0]);
  int f = fork();
  if (f) {
    //if (strcmp(parsed_line[0], "cd") == 0) {
      //chdir(parsed_line[1]);
      //printf("%d:%s", errno, strerror(errno));
    //}
    int status;
    wait( &status );
  } else {
    execvp(parsed_line[0], parsed_line);
  }
}

void cd(char* new_path){
  char path[1024];
  strcpy(path,new_path);
  char cwd[256];
  getcwd(cwd,sizeof(cwd));
  strcat(cwd,"/");
  strcat(cwd,path);
  chdir(cwd);
  print_dir();
}

char** run_the_shell(char *command_input, char *split_input, char ** cmd) {
  fgets(command_input, 256, stdin);

  // fgets appends a new line to the end of the string, this gets rid of it.
  char * newline_char;
  while( (newline_char = strstr(command_input, "\n")) ) {
    *newline_char = 0;
  }

  replace_str(command_input," ; ",";");
  replace_str(command_input,"; ",";");
  replace_str(command_input," ;",";");

  split_line(command_input, ";", split_input, cmd);
  return cmd;
}
void check_exit(char* token){
if (strcmp(token, "exit") == 0) {
    printf("\nbyebye buddy\n");
    exit(0);
  }
}
void print_dir() {
  char workingdir[1024];
  //strcat(workingdir,cwd);
  getcwd(workingdir,sizeof(workingdir)); //gets current working directory
  printf("C-SHELL %s $ ", workingdir);
}

void main() {
  char command_input[256]; // user input string
  char split_cmd[256];     // input string, but with NULLs instead of semicolons
  char *cmd[256];          // array of strings from split_cmd

  char split_command[256]; // single command string from cmd
  char *parsed_line[256];  // command string, but with NULLS instead of spaces

  char *init[] = {"clear", NULL};
  execute(init);

  while(1) {
    print_dir();

    // reset memory
    memset(command_input, 0, 256);
    memset(split_cmd, 0, 256);
    memset(cmd, 0, 256);

    // make split_cmd and cmd based on the contents of command_input
    run_the_shell(command_input, split_cmd, cmd);

    int i = 0;
    while ( cmd[i] ) {
      printf("cmd[%d]:\t%s\n", i, cmd[i]);
      check_exit(cmd[i]);
      // reset memory
      memset(split_command, 0, 256);
      memset(parsed_line, 0, 256);

      // make split_command and parsed_line based on contents of cmd[i]
      split_line(cmd[i], " ", split_command, parsed_line);
      printf("@%s\n", parsed_line[0]);

      execute(parsed_line);
      printf("\n--------------------------------\n");

      i++;
    }
  }
}
