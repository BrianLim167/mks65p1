#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

char ** parse_args(char* line){
  char ** retans = malloc(100* sizeof(char*));
  int i=0;
  while(line){
    retans[i]= strsep(&line," ");
    printf("retans[%d]= %s\n",i,retans[i]);
    printf("line:%s\n",line);
    printf("\n\n\n\n");
    i+=1;
  }

  return retans;
}


int parse(char* line){

  /*
    I think this should be moved to parse()

    if (!fork()) execlp("clear", "clear", NULL);

    char input[256];
    char token[256]

    scanf("%s", input);

    while (token = strsep(&input, ";"));

    return 0;
  */

  return 0;
}
//idk if this works
void execute(char** cmd){
  int f=fork();
  if(f==0){
    printf("\nchild executing...\n");
    execvp(cmd[0],cmd);
  }
  else{
    int status;
    printf("waiting\n");
    wait( &status );
  }
}

char** run_the_shell(){
  char *command_input=malloc(100*sizeof(char));
  char ** cmd;//commands string
  char workingdir[500];//current working directory
  getcwd(workingdir,sizeof(workingdir));//(man getcwd for info) it gets current working directory
  printf("C-SHELL... %s $ ",workingdir);
  //user input part:
  fgets(command_input,sizeof(command_input),stdin);//(destination,bytes,file pointer)
  if(strcmp(command_input,"exit\n")==0){
    printf("\nbyebye buddy\n");
    exit(0);
  }
  //fgets appends a new line to the end of the string, this gets rid of it.
  char * newline_char;
  while(newline_char = strstr(command_input,"\n")){
    //printf("%s##",command_input);
    *newline_char=0;
    //printf("%s##",command_input);
  }
  cmd= parse_args(command_input);

  return cmd;
}

void main(){//void so it doesn't exit the program
  while(1){
    char** cmd=malloc(100*sizeof(char*));
    cmd=run_the_shell();
    //int f=fork();
    execute(cmd);
  }
}
