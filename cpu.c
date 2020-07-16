#include <stdio.h>
#include <stdlib.h>
#include "oslabs.h"

int is_NULLpcb(struct PCB inpcb)
{
    if(inpcb.process_id == 0 & inpcb.arrival_timestamp == 0 && inpcb.total_bursttime == 0 && inpcb.execution_starttime == 0 & inpcb.execution_endtime ==
    0 && inpcb.remaining_bursttime == 0 && inpcb.process_priority == 0)
    return 1;
    else
        return 0;    
}

/*handle_process_arrival_pp*/
/* This function implements the logic to handle the arrival of a new process in a priority-based preemptive scheduler.
It takes five inputs:
1.	the ready queue (an array of PCB structs) 
2.	The number of items in the ready queue
3.	the PCB of the currently running process 
4.	the PCB of the newly arriving process 
5.	the current timestamp. 

The method determines the process to execute next and returns its PCB. */

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
    {
        if(is_NULLpcb(current_process))
		/* If the current_process is all zeroes, aka: is_NULLpcb, then...*/
		/*If there is no currently-running process (i.e., the third argument of handle_process_arrival_pp is the NULLPCB), 
		then the method returns the PCB of the newly-arriving process or new_process*/
		{
			new_process.execution_starttime = timestamp; 						/* the PCB of the new process is modified so that the execution start time is set to the current timestamp */
			new_process.execution_endtime = timestamp + new_process.total_bursttime; 		/* Set execution_endtime equal to time plus remaining_bursttime of the new_process*/
			new_process.remaining_bursttime = new_process.total_bursttime; 				/* set remaining_bursttime equal to total_bursttime */
			return new_process; 									/* this is the new_process */
		}
		/* */
		else if (new_process.process_priority >= current_process.process_priority) 
		/*If there is a currently-running process, the method compares the priority of the newly-arriving process with the currently-running process*/
		{
			new_process.execution_starttime = 0; 						/*As the newly-arriving process is added to the ready queue, its execution start time and execution end time are set to 0*/
			new_process.execution_endtime = 0;
			new_process.remaining_bursttime = new_process.total_bursttime; 			/*the remaining burst time is the same as its total burst time*/
			ready_queue[*queue_cnt] = new_process;
			(*queue_cnt)++;
			return current_process;
		}
		else
		{
			new_process.execution_starttime = timestamp; 					/*In this case, the PCB of the new process is modified so that the execution start time is set to the current timestamp*/
			new_process.execution_endtime = timestamp + new_process.total_bursttime;	/*the execution end time is set to the sum of the current timestamp and the total burst time */
			new_process.remaining_bursttime = new_process.total_bursttime;			/*the remaining burst time is set to the total burst time*/
			current_process.execution_endtime = 0;
			current_process.remaining_bursttime = new_process.total_bursttime;
			ready_queue[*queue_cnt] = current_process; 					/*the PCB of the currently-running process is added to the ready queue after marking its execution end time as 0 and adjusting its remaining burst time*/
			(*queue_cnt)++;
			return new_process;
		}
    }
/*************************************************************************************************************************************************************************************/	

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp)
/*This method implements the logic to handle the arrival of a new process in a Shortest-Remaining-Time-Next Preemptive Scheduler. Specifically, it takes five inputs: 
1.	the ready queue (an array of PCB structs) 
2.	The number of items in the ready queue
3.	the PCB of the currently-running process 
4.	the PCB of the newly-arriving process 
5.	the current timestamp. The method determines the process to execute next and returns its PCB. 
*/
{
	if(is_NULLpcb(current_process))
	/*If there is no currently-running process (i.e., the third argument is the NULLPCB), then the method returns the PCB of the newly-arriving process*/
	{	new_process.execution_starttime = time_stamp;					/*the execution end time is set to the sum of the current timestamp */
		new_process.execution_endtime = time_stamp + new_process.total_bursttime;	/*the execution end time is set to the sum of the current timestamp and the total burst time   */
		new_process.remaining_bursttime = new_process.total_bursttime; 			/*the remaining burst time is set to the total burst time.*/
		return new_process; 								/*the method returns the PCB of the newly-arriving process*/
	}
	else if(current_process.remaining_bursttime < new_process.remaining_bursttime)
	/*If there is a currently-running process, the method compares the remaining burst time of the currently-running process and the total burst time of the newly-arriving process. */
	{	new_process.execution_starttime = 0;
		new_process.execution_endtime = 0;					/*execution start time and execution end time are set to 0*/
		new_process.remaining_bursttime = new_process.total_bursttime; 		/*the remaining burst time is the same as its total burst time*/
		ready_queue[*queue_cnt] = new_process;					/*newly-arriving process is added to the ready queue*/
		(*queue_cnt)++;
		return current_process;
	}
	else
	{
		new_process.execution_starttime = time_stamp;					/*the PCB of the new process is modified so that the execution start time is set to the current timestamp*/
		new_process.execution_endtime = time_stamp + new_process.total_bursttime;	/*the execution end time is set to the sum of the current timestamp and the total burst time */
		new_process.remaining_bursttime = new_process.total_bursttime; 			/*the remaining burst time is set to the total burst time*/
		current_process.execution_starttime = 0;
		current_process.execution_endtime = 0;						/*the PCB of the currently-running process is added to the ready queue, after marking */
		ready_queue[*queue_cnt] = current_process;					/*execution start time and execution end time as 0*/
		(*queue_cnt)++;
		return new_process;
	}
}

/*************************************************************************************************************************************************************************************/

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
/*This method implements the logic to handle the arrival of a new process in a Round-Robin Scheduler. Specifically, it takes six inputs: 
1.	the ready queue (an array of PCB structs) 
2.	The number of items in the ready queue
3.	the PCB of the currently-running process 
4.	the PCB of the newly-arriving process  
5.	the current timestamp 
6.	the time quantum. 
*/
{
	if(is_NULLpcb(current_process))
	{	new_process.execution_starttime = timestamp;
		if (new_process.total_bursttime > time_quantum)
		{
			new_process.execution_endtime = timestamp + time_quantum;
		}
		else 
		{
			new_process.execution_endtime = timestamp + new_process.total_bursttime;
		}
		new_process.remaining_bursttime = new_process.total_bursttime;
		return new_process;
	}
	
	else 
	{
		new_process.execution_starttime = 0;
		new_process.execution_endtime = 0;					/*execution start time and execution end time are set to 0*/
		new_process.remaining_bursttime = new_process.total_bursttime; 		/*the remaining burst time is set to the total burst time*/
		ready_queue[*queue_cnt] = new_process;
		(*queue_cnt)++;
		return current_process;
	}
		
	
}
/*************************************************************************************************************************************************************************************/

struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum)
/* This method implements the logic to handle the arrival of a new process in a Round-Robin Scheduler. Specifically, it takes six inputs: 
1.	the ready queue (an array of PCB structs) 
2.	The number of items in the ready queue
3.	the PCB of the currently-running process 
4.	the PCB of the newly-arriving process  
5.	the current timestamp 
6.	the time quantum. 

The method determines the process to execute next and returns its PCB. 
*/
{
	
}
/*************************************************************************************************************************************************************************************/
struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
/*This method implements the logic to handle the completion of execution of a process in a Priority-based Preemptive Scheduler. Specifically, it takes three inputs: 
1.	the ready queue (an array of PCB structs) 
2.	The number of items in the ready queue
3.	the current timestamp. 

The method determines the process to execute next and returns its PCB. 
*/
{
	if(*queue_cnt = 0)
	{
		return is_NULLpcb;
	}
	else
		
}
/*************************************************************************************************************************************************************************************/
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{
	
}

