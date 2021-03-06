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
    if( strcmp(parsed_line[1],"~")==0){
      chdir(getenv("HOME"));
    }
    if(parsed_line[1]){
      chdir(parsed_line[1]);
    }
    else{
      chdir(getenv("HOME"));
    }
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
  getcwd(workingdir,sizeof(workingdir)); //gets current working directory
  printf("C-SHELL %s $ ", workingdir);
}

/**
 * @Function: locate_redirect
 * @Params: char ** parsed_line
 * @Returns: int red_index
 * @Explanation: It searches through the parsed line to find the index of <, > or |
 */
int locate_redirect(char ** parsed_line ){
  int red_index=0;
  while(parsed_line[red_index]){
    if (!strcmp(parsed_line[red_index],">") || !strcmp(parsed_line[red_index],"<") || !strcmp(parsed_line[red_index],"|")){

      return red_index;
    }
    red_index++;
  }
  return 0;// used as false later
}
/**
 * @Function: locate_symbol
 * @Params: char ** parsed_line, char * symbol
 * @Returns: int red_index
 * @Explanation: Similar to locate_redirect but it specifies the symbol.
 */
int locate_symbol(char ** parsed_line, char* symbol){
  int red_index=0;
  while(parsed_line[red_index]){
    if (!strcmp(parsed_line[red_index],symbol)){
      return red_index;
    }
    red_index++;
  }
  return 0;
}
/**
 * @Function: zero
 * @Params: char ** parsed_line, int redirection
 * @Returns: void
 * @Explanation:This function zeros out everything except for the command in parsed_line
 */

void zero(char** parsed_line, int redirection){
  int i = redirection;
  while (parsed_line[i]) {
    parsed_line[i] = 0;
    i++;
  }
}

/**
 * @Function: exec
 * @Params: int forked, char ** parsed_line
 * @Returns: None
 * @Explanation: This is super similar to execute except it's takes an int as a parameter so that we can implement modular design and make our functions shorter.
 */

void exec(int forked, char** parsed_line){
  if (!forked){
    execvp(parsed_line[0],parsed_line);
  }else{
    int status;
    wait(&status);
  }
}
/**
 * @Function: redirect
 * @Params: char ** parsed line
 * @Returns: None
 * @Explanation: Uses modular design( locate_redirect, locate_symbol, zero, and exec) so that redirection and multiple redirection can work.
 */
void redirect(char **parsed_line){
  int redirection= locate_redirect(parsed_line);
  int i=0;
  if(redirection){
    char* red= parsed_line[redirection];
    int f;
    int newfr;
    int newfw;
    FILE *newsr;
    FILE *newsw;
    int currfr;
    int currfw;
    int in_index = locate_symbol(parsed_line, "<");
    int out_index = locate_symbol(parsed_line, ">");
    if ( in_index && out_index ) {
      f = fork();
      if (!f) {
        char *in = parsed_line[in_index + 1];
        char *out = parsed_line[out_index + 1];
        newfr = open(in, O_CREAT | O_RDONLY, 0644);
        newfw = open(out, O_CREAT | O_WRONLY, 0644);
        currfr = dup(0);
        currfw = dup(1);
        dup2(newfr, 0);
        dup2(newfw, 1);
        zero(parsed_line, in_index);
        zero(parsed_line, out_index);
        exec(fork(), parsed_line);
        dup2(currfr, STDIN_FILENO);
        dup2(currfw, STDOUT_FILENO);
        close(newfr);
        close(newfw);
        exit(0);
      } else {
        int status;
        wait(&status);
      }
    } else if(!strcmp(red,"<")) {
      f=fork();
      if(!f){
        red=parsed_line[redirection+1];
        newfr=open(red,O_CREAT|O_RDONLY,0644);
        currfr=dup(0);
        dup2(newfr,0);
        zero(parsed_line,redirection);
        int fo = fork();
        exec(fo,parsed_line);
        dup2(currfr,STDIN_FILENO);
        close(newfr);
        exit(0);
      }
      else{
        int status;
        wait(&status);
      }
    } else if(!strcmp(red,">")) {
      f=fork();
      if(!f){
        red=parsed_line[redirection+1];
        newfw=open(red,O_CREAT|O_WRONLY,0644);
        currfw=dup(1);
        dup2(newfw,1);
        zero(parsed_line,redirection);
        int fo = fork();
        exec(fo, parsed_line);
        dup2(currfw,STDOUT_FILENO);
        close(newfw);
        exit(0);
      }
      else{
        int status;
        wait(&status);
      }
    }
    else if( !strcmp(red,"|") ){
      f=fork();
      if(!f){
        char command0[256];
        char command1[256];
        char pipe_info[256];
        memset(command0, 0, 256);
        memset(command1, 0, 256);
        memset(pipe_info, 0, 256);
        int i = 0;
        while (strcmp(parsed_line[i], "|")) { // command0 is everything before |
          strcat(command0, parsed_line[i]);
          strcat(command0, " ");
          i++;
        }
        i++;
        while (parsed_line[i]) { // command1 is everything after |
          strcat(command1, parsed_line[i]);
          strcat(command1, " ");
          i++;
        }

        newsw = popen(command1,"w");
        newsr = popen(command0,"r");
        newfr = fileno(newsr);
        newfw = fileno(newsw);
        read(newfr, pipe_info, 256);
        write(newfw, pipe_info, 256);
        close(newfr);
        close(newfw);
        pclose(newsr);
        pclose(newsw);
        exit(0);
      } else {
        int status;
        wait(&status);
      }
    }
  }

}


int main() {
  char command_input[256]; // user input string
  char split_cmd[256];     // input string, but with NULLs instead of semicolons
  char *cmd[256];          // array of strings from split_cmd

  char split_command[256]; // single command string from cmd
  char *parsed_line[256];  // command string, but with NULLS instead of spaces

  char *init[] = {"clear", NULL};
  //execute(init);

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
      if (locate_redirect(parsed_line)){
        redirect(parsed_line);

      } else {
        execute(parsed_line);
      }
      //print_dir();
      printf("\n--------------------------------\n");

      i++;
    }
  }
  return 0;
}
