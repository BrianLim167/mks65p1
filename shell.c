#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>



int parse(){

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


/*main will call all other functions.
 * So it will print a shell line for inputs
 * and then call all the other functions that we end up writing. 
 */
int main(){
  
  char command_input[500];
  char * cmd[100];//commands string
  char workingdir[500];//current working directory

  getcwd(workingdir,sizeof(workingdir));//(man getcwd for info) it gets current working directory
  printf("C-SHELL... %s $ ",workingdir);
  //user input part:
  fgets(command_input,sizeof(command_input),stdin);//(destination,bytes,file pointer)

  return 0;
}
  
