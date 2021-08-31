#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
    /************************************************** command line arguments ***********************************************
        For the purposes of this explanation, assume that "external_program.out" is located in /home/usr/A1/external_program.out

        When you are testing your program, replace "/home/usr/A1/external_program.out" with the path to the executable file
        generated when you compile "external_program.c"

        To compile assignment1.c: gcc assignment1.c -o assignment1
        To run your program: ./assignment1 /home/usr/A1/external_program.out
        argv[0] = "./assignment1"
        argv[1] = "/home/usr/A1/external_program.out"

        Number of arguments (argc) = 2

        In this assignment, the path to the external program is in argv[1]
    *************************************************************************************************************************/

    // If the path of external_program.out isn't provided by the user, the program will terminate
    if (argc != 2)
    {
    printf("Invalid arguments\n");
    exit(0);
    }

    // You must insert the following into your code (Replace zeros with the appropriate values/variables)
    //printf("parent process (PID %d) created child_1 (PID %d) \n", 0, 0);
    //printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", 0, 0);
    //printf("child_1 (PID %d) created child_1.1 (PID %d)\n", 0, 0);
    //printf("child_1 (PID %d) is now complete\n", 0);
    //printf("parent (PID %d) created child_2 (PID %d)\n", 0, 0);
    //printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2..\n", 0);

    // Hint: You might find snprintf() helpful in this assignment



    /***************************************************************************************************
     * 										 YOUR CODE GOES HERE
     ***************************************************************************************************/

    pid_t i, pid_1, pid_2, pid_3;

    pid_1 = fork();

    if (pid_1 < 0){

        printf("The fork is unsuccessful");
        exit(1);
    }
    if (pid_1 > 0){  // if parent process

        i = getpid();  // getting parent's PID
        printf("parent process (PID %d) created child_1 (PID %d)\n", i, pid_1);
        printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", i, pid_1);
        wait(NULL);  // blocking the calling process until child_1 terminates
    }

    if (pid_1 == 0){  // if child_1

        pid_2 = fork();

        if (pid_2 > 0) {  // in this case, checking if child_1.1

            i = getpid();  // getting child_1's PID
            printf("child_1 (PID %d) created child_1.1 (PID %d)\n", i, pid_2);
        }

        if (pid_2 != 0){  // if child_1 finished execution

            i = getpid();   // getting child_1's PID
            printf("child_1 (PID %d) is now complete\n", i);
        }

    }else {  // the parent will go here after resuming at wait(NULL)

        pid_3 = fork();

        if (pid_3 > 0) {   // in this case, checking if child_2

            i = getpid();  // getting parent's PID
            printf("parent (PID %d) created child_2 (PID %d)\n", i, pid_3);
            printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2..\n", pid_3);

            char PID_child_2[20];
            sprintf(PID_child_2, "%d", pid_3);

            argv[1] = PID_child_2;  // we want to pass this to execl() as argv[1] a not just PID_child_2, so that external_program can see/access the argv[1]


            // execl() with the local path for local testing

            execl("/Users/matveyskripchenko/CLionProjects/3305_Assignment_1/external_program.out", argv[0], argv[1], (char*) NULL);

            // execl() with the remote path for remote testing

            execl("/home/mskripch/external_program.out", argv[0], argv[1], (char*) NULL);
        }
    }

    return 0;
}