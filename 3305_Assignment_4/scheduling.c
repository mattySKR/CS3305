#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "scheduling.h"

// Student: Matvey Skripchenko
// Student number: 250899673

// helper function for adding the node to the end of LL
void addfront(struct node** head, int new_val)
{
    // allocating memory for the node
    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    // will relate to the while loop below
    struct node *last = *head;

    // setting up data for the node
    new_node->value  = new_val;

    // making the last node point to NULL (i.e. is last node)
    new_node->next = NULL;

    // if linked list is empty, making the
    // last node a new head node
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    // if not empty then we traverse
    // till we reach the last node
    while (last->next != NULL)
        last = last->next;

    // second last node will point
    // to the new node
    last->next = new_node;

}

// helper function for getting the # of nodes in the LL
int getCount(struct node* head)
{
    // setting up count
    int count = 0;

    // setting up current node to
    // point to head node
    struct node* current = head;

    // traverse through LL until reach the end
    while (current != NULL)
    {
        // increment count
        count++;
        // point current to the next node in LL
        current = current->next;
    }
    return count;
}

// helper function to get the value of the Nth node in LL
int GetNth(struct node* head, int index) {

    // point current node to the head
    struct node *current = head;

    // setting index for the node
    // we currently pointing to
    int count = 0;

    // traverse until the end of LL
    while (current != NULL) {
        // if our increment matches
        // the index of the node
        if (count == index)
            // return the nodes value
            return (current->value);
        count++;
        // point current to the next node
        current = current->next;
    }
    assert(0);
}

/*
##  Round-Robin Scheduling Algorithm  ##

	Parameters:-

	queue: 1D int array containing the CPU burst time for every process in a ready queue
	np: number of processes (length of `queue` array)
	tq: time quantum for the RR algorithm


	Returns:-

	rr_result struct pointer, where
	rr_result -> order: 1D int array, containing the execution order of processes (i.e. `(rr_result -> order)[0]` is the process number of the first process)
		** hint: p1 is always the first item in order of selection in round-robin and FCFS
    rr_result -> order_n: int, representing the size of the `order` array, described above ^
	rr_result -> turnarounds: 1D int array, containing the turnaround time for each process (i.e. `(rr_result -> turnarounds)[0]` is the turnaround time for p1)
*/


rr_result *rr(int *queue, int np, int tq)
{

	rr_result *result = malloc(sizeof(rr_result));
	result->np = np;
	result->turnarounds = malloc(sizeof(int) * np);

	// code here to assign values to result->turnarounds, result->order, and result->order_n

    // setting up new head, so point to NULL
    node* head = NULL;

    // 1-D array of burst times for each process
    int leftover_queue[np];

    // 1-D array of total wait times of each
    // //process until completion
    int wait_time[np];

    // current time total for each process
    int current_time;

    // 1-D array of arrival times for each process
    int start_exec[np];

    // arrival time total for each process
    int start_total;

    // initializing the above
	for (int i = 0; i < np; i++){

		leftover_queue[i] = queue[i];
		wait_time[i] = 0;
        start_exec[i] = 0;
        addfront(&head,i);
	}

    start_total = 0;
	// here, setting up arrival times for each process
    for (int i = 0; i < np; i++){

        // arrival time for the first process
        // has to be zero, t = 0
        if(i==0){

            start_exec[0] = start_total;

            // if the process burst time is greater
            // than time quantum
            if(leftover_queue[0] < tq){

                // then add its burst time to the total
                start_total += leftover_queue[0];
            }
            else{
                //otherwise (>= tq), add time quantum
                // to the total
                start_total += tq;
            }
        }
        else{
            // if any process besides the first one
            // has a burst time less than time quantum
            if(leftover_queue[i] < tq){

                // assign the arrival total to the process
                start_exec[i] = start_total;

                // get its burst time < tq from the queue
                // and assign to the arrival total
                start_total += leftover_queue[i];

            }else{
                // otherwise (>= tq), add time quantum,
                // so assign arrival total to the process
                start_exec[i] = start_total;

                // increment arrival total by time quantum
                start_total += tq;

            }
        }
    }
	current_time = 0;

    // now onto cycling through all processes' burst times
    // until each process is complete (burst time = 0)
    // in a RR manner
	while (1) {

        // setting up boolean to true for
        // infinite loop exit
        bool finished = true;

        // cycling through each process on order
        // /over and over again
        for (int i = 0; i < np; i++) {

            // if the process burst time is greater
            // than 0, i.e. it has not yet completed
            if (leftover_queue[i] > 0) {

                // keep going
                finished = false;

                // if process leftover burst time is
                // greater than time quantum
                if (leftover_queue[i] > tq) {

                    // add time quantum to current time total
                    current_time += tq;

                    // decrement the leftover burst time of
                    // the process by time quantum
                    leftover_queue[i] -= tq;

                    // add the number of the process to the LL
                    // to keep the order of execution
                    addfront(&head, i);

                } else {
                    // otherwise, the process's leftover burst time
                    // is (tq <=), i.e. the process is on its last
                    // cycle of execution by CPU

                    // add the leftover burst time of the process to
                    // the current time total
                    current_time += leftover_queue[i];

                    // assigning the total current time of execution
                    // to the process
                    wait_time[i] += current_time;

                    // setting the burst time of that process to 0
                    // i.e. process has completed
                    leftover_queue[i] = 0;
                }
            }
        }
        // if every process in the
        // queue has completed
        if (finished == true) {

            // exit the loop
            break;
        }
    }

    // cycling through each process in the
    // 1-D turnaround time array
    for (int i = 0; i < np; i++){

        // turnaround time = wait time(completion time) - arrival time
        (result->turnarounds)[i] = wait_time[i] - start_exec[i];

    }

    // get the length of the executions LL
    int queue_length = getCount(head);

    // assign that execution length
    // value to ready queue
    result->order_n = queue_length;

    // allocate memory for the order of
    // execution of ready queue
    // by the length/size of that execution queue
    result->order = malloc(sizeof(int) * queue_length);

    // cycle through the all indexes in the 1-D
    // execution order array and assign
    // a process number to each index
    for (int i = 0; i < queue_length; i++){

        // extracting the process number from LL
        // and assign it to the index in exec order
        // array
        (result->order)[i] = GetNth(head,i);

    }
    return result;
}