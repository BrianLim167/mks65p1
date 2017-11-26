#include "shell.h"

/*
char ** parse_args(char* line, char ** retans) {
  int i=0;
  while(line) {
    retans[i]= strsep(&line," ");
    printf("retans[%d]= %s\n",i,retans[i]);
    printf("line:%s\n",line);
    printf("\n\n\n\n");
    i+=1;
  }
  return retans;
}
*/

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

// not 100% done yet.
/*
char** parse_multiple_commands(char* line, char ** retans) {
  int i = 0;
  while(line) {
   retans[i]=strsep(&line,";");
   i++;
  }
  printf("i: %d\n",i);
  return retans;
}
*/

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

  split_line(command_input, ";", cmd);
  return cmd;
}

void print_dir() {
  char workingdir[1024];
  getcwd(workingdir,sizeof(workingdir)); //gets current working directory
  printf("C-SHELL %s $ ", workingdir);
}

void main() {
  char *init[] = {"clear", NULL};
  execute(init);
  while(1) {
    print_dir();
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
