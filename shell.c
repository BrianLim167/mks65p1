#include "shell.h"


// changes retans to contain the tokens of line as determined by character
char ** split_line(char* line, char* character, char ** retans) {
  int i=0;
  char input[256];
  strcpy(input,line);
  char *input_pointer = input;
  while (retans[i] = strsep(&input_pointer, character)) {
    i++;
  }
  retans[i] = 0; // NULL termination
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
    //if (parsed_line[0] == "cd") chdir(parsed_line[1]);
    int status;
    wait( &status );
  } else {
    execvp(parsed_line[0], parsed_line);
  }
}

void cd(char* new_path){
  char path[1000];
  strcpy(path,new_path);
  char cwd[256];
  getcwd(cwd,sizeof(cwd));
  strcat(cwd,path);
  chdir(cwd);
  print_dir();
}


char** run_the_shell(char ** cmd) {
  char command_input[256];
  fgets(command_input, sizeof(command_input), stdin);

  // fgets appends a new line to the end of the string, this gets rid of it.
  char * newline_char;
  while( (newline_char = strstr(command_input, "\n")) ) {
    *newline_char = 0;
  }

  if (strcmp(command_input, "exit") == 0) {
    printf("\nbyebye buddy\n");
    exit(0);
  }
  replace_str(command_input," ; ",";");
  replace_str(command_input,"; ",";");
  replace_str(command_input," ;",";");
  split_line(command_input, ";", cmd);
  return cmd;
}

void print_dir(char* cwd) {
  char workingdir[1024];
  //strcat(workingdir,cwd);
  getcwd(workingdir,sizeof(workingdir)); //gets current working directory
  printf("C-SHELL %s $ ", workingdir);
}

void main() {
  char *init[] = {"clear", NULL};
  execute(init);
  while(1) {
    char* cwd;
    getcwd(cwd,sizeof(cwd));
    print_dir(cwd);
    char **cmd = (char **)calloc(256, sizeof(char *));
    run_the_shell(cmd);
    int i = 0;
    while( cmd[i] ) {
      printf("cmd[%d]:\t%s\n", i, cmd[i]);
      char **parsed_line = (char **)calloc(256, sizeof(char *));
      split_line(cmd[i], " ", parsed_line);
      printf("@%s\n", parsed_line[0]);
      execute(parsed_line);
      free(parsed_line);
      printf("\n--------------------------------\n");
      i++;
    }
    free(cmd);
  }
}
