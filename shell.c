#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>



int parse(){

  return 0;
}


/*main will call all other functions.
 * So it will print a shell line for inputs
 */
int main(){
  
  char c[500];//input command
  char * cmd[100];//commands string
  char workingdir[500];//current working directory

  getcwd(workingdir,sizeof(workingdir));//(man getcwd for info) it gets current working directory
  printf("C-SHELL... %s $ ",workingdir);
  
  return 0;
}
  /*
  if (!fork()){
    execlp("clear", "clear", NULL);
  }
  char input[256];
  char token[256];
  scanf("%s", input);

  while (token = strsep(&input, ";"));
  
  return 0;

  */
