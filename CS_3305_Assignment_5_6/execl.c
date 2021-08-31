#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
 

/*
  Simple program that uses execl

*/

int main() {

  int status;
  pid_t pid;

  pid = fork();

  if (pid > 0) {
    printf("Hello from parent...");
    wait(NULL);
    printf("Hello from parent after child is completed\n");

  }

  if (pid == 0) {
    printf("Hello from child...going to call execl now..\n");
    status = execl("external", "external", NULL);
    printf("\n From Child after execl call");


    if (status < 0)
      printf("\n main: execl failed\n");
  }
}
 