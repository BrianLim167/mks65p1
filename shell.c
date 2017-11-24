#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "headers.h"

char ** parse_args(char* line){
  char ** retans = (char **) malloc(100* sizeof(char*));
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

//general splitting function:
char** split_line(char* line, char* character){
  char ** retans=(char**) malloc(100*sizeof(char*));
  int i=0;
  char * input=malloc(100*sizeof(char));
  input=line;
  while(input){
    retans[i]=strsep(&input,character);
    i+=1;
  }
  return retans;
}


void execute(char** cmd){
  int f=fork();
  if(f==0){
    // printf("\nchild executing...\n");
    execvp(cmd[0],cmd);
  }
  else{
    int status;
    //printf("waiting\n");
    wait( &status );
  }
}

//not 100% done yet.
char** parse_multiple_commands(char* line){

  char ** retans=malloc(100*sizeof(char*));
  int i=0;
  while(line){
   retans[i]=strsep(&line,';');
   i++;
  }
  printf("i: %d\n",i);
  return retans;
}



char** run_the_shell(){
  char *command_input=malloc(100*sizeof(char));
  char ** cmd;//commands string

  //user input part:
  fgets(command_input,sizeof(command_input),stdin);//(destination,bytes,file pointer)
  if(strcmp(command_input,"exit\n")==0){
    printf("\nbyebye buddy\n");
    exit(0);
  }
  //fgets appends a new line to the end of the string, this gets rid of it.
  char * newline_char;
  while( (newline_char = strstr(command_input,"\n")) ){
    *newline_char=0;

  }
  cmd=split_line(command_input,";");
  int x=0;
  return cmd;
}

void print_prompt(){
  char workingdir[500];//current working directory
  getcwd(workingdir,sizeof(workingdir));//(man getcwd for info) it gets current working directory
  printf("C-SHELL... %s $ ",workingdir);
}
void main(){//void so it doesn't exit the program
  while(1){
    print_prompt();
    char** cmd=malloc(100*sizeof(char*));
    cmd=run_the_shell();
    int x=0;
    while(cmd[x]){
      printf("cmd[%d] in main: %s\n\n",x,cmd[x]);
      execute(split_line(cmd[x]," "));
      x++;
    }

  }
}
