#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
 

/*
   This program illustrates fork() with the file descriptor. It opens a file before fork()
*/

 
int main()

{
    int fd;
    char c;
    pid_t pid;

    fd = open("hello.txt", O_RDONLY);

    pid = fork ();

    
    if (pid > 0){

        read(fd, &c, 1);
        printf("parent: c = %c\n", c);
        wait(NULL);
    }
    else if (pid == 0) {
       read(fd, &c, 1);
       printf("child: c = %c\n", c);

    }
 
   return 0;
}
