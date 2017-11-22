#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
  if (!fork()) execlp("clear", "clear", NULL);

  char input[256];
  char token[256]
  
  scanf("%s", input);

  while (token = strsep(&input, ";"));
  
  return 0;
}
