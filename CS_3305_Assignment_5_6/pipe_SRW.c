#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(void){
  int n;
  int status;
  char c;
  int port[2];
  pid_t pid;
 
  if (pipe(port) < 0){
    perror("pipe error");
    exit(0);
  } 

  pid = fork();
  if (pid < 0) {
    perror("fork error");
    exit(0);
  }

  if(pid > 0) //parent
  {
    printf("\n From parent: writing to pipe now..");
    write(port[1],"ABC\n",4);
    printf("\n From parent: waiting for child to complete..\n");
    wait(NULL);
    
  
  } else //child
   
  {
    printf("\n From Child: reading from the pipe now..");
    read (port[0],&c,1);
    printf("\n from child: this is what I read %c", c);


  }

  return 0;

}
