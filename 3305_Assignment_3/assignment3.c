#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>


int x, y, z; 

void *sum(){
	z=y+x;
	return NULL;
}

int main() {

    pid_t child;
    pthread_t thread;

    // Initializing the global variables
	x=10, y=20, z=0;

    // create child process
    child = fork();

	// check for child creation error
    if (child < 0) {

        printf("main function: errno  is %d\n", errno);

    }

	// in parent:
    else if (child > 0){

        // wait for child, and print value of z
        wait(NULL);
        printf("Using a fork(), the value of z in the parent process is: %d\n", z); //value of z after the fork process won't change

        // create thread, wait for it to complete, then print value of z
        pthread_create(&thread, NULL, sum, NULL);
        pthread_join(thread, NULL);
        printf("Using a thread, the value of z is: %d\n", z); //value of z after passing to the thread will change
    }

    // in child:
    else{

        // sum x and y and store it in z
        z = x+y;
        // print value of z
        printf("Using a fork(), the value of z in the child process is: %d\n", z);
    }
    return 0;
}