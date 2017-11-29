#include "shell.h"

/**
 * @Function: split_line
 * @Params: char* line, char * character,char* split_input, char** retans
 * @Returns: char**
 * @Explanation: splits the line at the character. If multiple occurrences each will be a token in retans.
 */

char ** split_line(char* line, char* character, char* split_input, char ** retans) {
  int i=0;
  strcpy(split_input,line);
  char *input_pointer = split_input;
  while(retans[i] = strsep(&input_pointer, character)) {
    i++;
  }
  //retans[i] = 0; // NULL termination
  return retans;
}


/**
 * @Function: replace_str
 * @Params: char* line, char* substring, char* replace_with
 * @Returns: Nothing
 * @Explanation: replaces the substring with replace_with. Used for if user surrounds semicolon with spaces.
 */
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

/**
 * @Function: execute
 * @Params: char** parsed_line
 * @Returns: Nothing
 * @Explanation: forks, parent waits for child to execute parsed_line
 */
void execute(char **parsed_line) {
  //printf("@@%s\n", parsed_line[0]);
  int f = fork();
  if (f) {
    int status;
    wait( &status );
  }
  else {
    execvp(parsed_line[0], parsed_line);
    exit(0);
  }
}

/**
 * @Function: cd
 * @Params: char ** parsed_line
 * @Returns: nothing
 * @Explanation: change directory function, includes cd with no param and cd ~ as well
 */
void cd(char** parsed_line){
  if(strcmp(parsed_line[0],"cd") == 0){
    // printf("\n\nparsed_line[0]: %s\n",parsed_line[0]);
    // printf("\nparsed_line[1]: %s\n",parsed_line[1]);
    if( strcmp(parsed_line[1],"~")==0){
      chdir(getenv("HOME"));
    }
    if(parsed_line[1]){
      chdir(parsed_line[1]);
    }
    else{
      chdir(getenv("HOME"));
    }
    // char path[256];
    //strcpy(path, strchr(parsed_line[1],"~")+1);
  }
}


/**
 * @Function: run_the_shell
 * @Params: char* command_input, char* split_input, char** cmd
 * @Returns: char **
 * @Explanation: gets user input, replaces "\n" with 0 after fgets, and uses replace_Str and split_line to populate cmd.
 */
char** run_the_shell(char *command_input, char *split_input, char ** cmd) {
  fgets(command_input, 256, stdin);
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


/**
 * @Function: check_exit
 * @Params: char * token
 * @Returns: Nothing
 * @Explanation: if the token is "exit" exit the program
 */
void check_exit(char* token){
  if(!strcmp(token, "exit")) {
    printf("\nbyebye buddy\n");
    exit(0);
  }
}

/**
 * @Function: print_dir
 * @Params: None
 * @Returns: None
 * @Explanation: Prints the prompt using current working directory
 */
void print_dir() {
  char workingdir[1024];
  //strcat(workingdir,cwd);
  getcwd(workingdir,sizeof(workingdir)); //gets current working directory
  printf("C-SHELL %s $ ", workingdir);
}

/**
 * @Function: locate_redirect
 * @Params:
 * @Returns:
 * @Explanation:
 */
int locate_redirect(char * cmd[] ){
  int red_index=0;
  while(cmd[red_index]){
    if (!strcmp(cmd[red_index],">") || !strcmp(cmd[red_index],"<") || !strcmp(cmd[red_index],"|")){
      return red_index;
    }
    red_index++;
  }
  return 0;// used as false later
}

/**
 * @Function: redirect
 * @Params:
 * @Returns:
 * @Explanation:
 */
void redirect(char* cmd[]){
  int redirection= locate_redirect(cmd);
  if(redirection){
    char* red= cmd[redirection];
    int f;
    int newf;
    int currf;
    if(!strcmp(red,"<")){
      f=fork();

      if(!f){
        red=cmd[(redirection+1)];
        newf=open(red,O_RDONLY);
        currf=dup(0);
        dup2(newf,0);
        cmd[redirection]=0;
        execvp(cmd[0],cmd);
        dup2(currf,0);
        close(newf);
      }

    }
    else if(!strcmp(red,">")){
      f=fork();
      if(!f){
        red=cmd[redirection+1];
        newf=open(red,O_CREAT|O_WRONLY);
        currf=dup(1);
        dup2(newf,1);
        cmd[redirection]=0;
        execvp(cmd[0],cmd);
      }
    }
    else{
      //TODO
    }
  }
}
//copy this for future functions:

/**
 * @Function:
 * @Params:
 * @Returns:
 * @Explanation:
 */
int main() {
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


      // reset memory
      memset(split_command, 0, 256);
      memset(parsed_line, 0, 256);

      // make split_command and parsed_line based on contents of cmd[i]
      split_line(cmd[i], " ", split_command, parsed_line);
      printf("@%s\n", parsed_line[0]);

      cd(parsed_line);
      check_exit(cmd[i]);
      redirect(parsed_line);
      execute(parsed_line);
      printf("\n--------------------------------\n");

      i++;
    }
  }
  return 0;
}
