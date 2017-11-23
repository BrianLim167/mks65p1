#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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

int execute(){
  
}

void run_the_shell(){
  char command_input[500];
  char ** cmd;//commands string
  char workingdir[500];//current working directory

  getcwd(workingdir,sizeof(workingdir));//(man getcwd for info) it gets current working directory
  printf("C-SHELL... %s $ ",workingdir);
  //user input part:
  fgets(command_input,sizeof(command_input),stdin);//(destination,bytes,file pointer)

  //printf("[command_input] %s \n",command_input);
  cmd= parse_args(command_input);
  // return 0;
}

/*main will call all other functions.
 * So it will print a shell line for inputs
 * and then call all the other functions that we end up writing. 
 */
void main(){//void so it doesn't exit the program
  
  run_the_shell();
}
  
