#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Reading and writing end of the pipe
#define READ_END 0
#define WRITE_END 1

int main(int argc, char **argv)
{

	/*************************************** command line arguments ***************************************
		To compile assignment2.c: gcc assignment2.c -o assignment2
		To run your program: ./assignment2 "CS" "3305" " is fun!"
		argv[0] = "./assignment2"
		argv[1] = "CS"
		argv[2] = "3305"
		argv[3] = " is fun!"

		Number of arguments (argc) = 4

		In this assignment, the parent process reads argv[1] and the child process reads argv[2] and argv[3]
		e.g. In the parent process: char *x = argv[1];
	*******************************************************************************************************/

	// If the user does not pass X, Y and Z, the program will terminate
	if (argc != 4)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	// You must insert the following into your code (Replace zeros with the appropriate values/variables)
	//printf("A pipe is created for communication between parent (PID %d) and child\n", 0);
	//printf("parent (PID %d) created a child (PID %d)\n", 0, 0);
	//printf("parent (PID %d) receives X = \"%s\" from the user\n", 0, 0);
	//printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n", 0, 0, 0);
	//printf("child (PID %d) concatenates Y and Z to generate Y'= %s\n", 0, 0);
	//printf("child (PID %d) writes Y' into the pipe\n", 0);
	//printf("parent (PID %d) reads Y' from the pipe (Y' = \"%s\")\n", 0, 0);
	//printf("parent (PID %d) concatenates X and Y' to generate the string: %s\n", 0, 0);

	// Note: You do not need to implement a function to concatenate two strings. "string.h" header file has been included



	/***************************************************************************************************
	 * 										   YOUR CODE GOES HERE										
	 ***************************************************************************************************/

#define size 25

	int fd[2];
    pid_t pid;

    char buff[size];  // used for parent



    if(pipe(fd) < 0){
        perror("Error creating the pipe, please try again");
        exit(0);
    }

    pid = fork();  // creating a fork

    if(pid < 0){
        perror("Error creating the fork, please try again");
        exit(0);
    }

    if(pid > 0){   // parent process

        printf("A pipe is created for communication between parent (PID %d) and child\n", getpid());

        char* X = argv[1];

        wait(NULL);

        read(fd[READ_END], buff, size);  // reading from the pipe
        printf("parent (PID %d) reads Y' from the pipe (Y' = \"%s\")\n", getpid(), buff);


        char final_string[size] = "";  // for concatenation purposes
        strcat(final_string, X);   // X
        strcat(final_string, buff);  // X concatenated with the contents of buff

        printf("parent (PID %d) concatenates X and Y' to generate the string: \"%s\"\n", getpid(), final_string);


    }else{    // child process

        printf("parent (PID %d) created a child (PID %d)\n", getppid(), getpid());
        printf("parent (PID %d) receives X = \"%s\" from the user\n", getppid(), argv[1]);

        char* Y = argv[2];
        char* Z = argv[3];

        printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n", getpid(), Y, Z);

        char conc_string[size] = "";
        strcat(conc_string,Y);  // Y
        strcat(conc_string,Z);  // Y concatenated with Z

        printf("child (PID %d) concatenates Y and Z to generate Y'= \"%s\"\n", getpid(), conc_string);

        write(fd[WRITE_END], conc_string, size);  // writing concatenated string to the pipe

        printf("child (PID %d) writes Y' into the pipe\n", getpid());

    }
	return 0;
}