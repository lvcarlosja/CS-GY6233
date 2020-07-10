#include <stdio.h>
#include "oslabs.h"

int is_NULLpcb(struct PCB inpcb)
{
    if(inpcb.process_id == 0 & inpcb.arrival_timestamp == 0 && inpcb.total_bursttime == 9 && inpcb.execution_starttime == 0 & inpcb.execution_endtime ==
    0 && inpcb.remaining_bursttime == 0 && inpcb.process_priority == 0)
    return 1;
    else
        return 0;    
}

/*handle_process_arrival_pp*/
struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
    {
        if(is_NULLpcb(current_process))
		{
			new_process.execution_starttime = timestamp;
			new_process.execution_endtime = timestamp + new_process.remaining_bursttime;
			new_process.remaining_bursttime = new_process.total_bursttime;
			return new_process;
		}
		else if (new_process.process_priority >= current_process.process_priority)
		{
			new_process.execution_starttime = 0;
			new_process.execution_endtime = 0;
			new_process.remaining_bursttime = new_process.total_bursttime;
			ready_queue[*queue_cnt] = new_process;
			(*queue_cnt)++;
			return current_process;
		}
		else
		{
			new_process.execution_starttime = timestamp;
			new_process.execution_endtime = timestamp + new_process.total_bursttime;
			new_process.remaining_bursttime = new_process.total_bursttime;
			current_process.execution_endtime = 0;
			current_process.remaining_bursttime = new_process.total_bursttime;
			ready_queue[*queue_cnt] = current_process;
			(*queue_cnt)++;
			return new_process;
		}
    }
/* This function implements the logic to handle the arrival of a new process in a priority-based preemptive scheduler.
It takes five inputs:
1.	the ready queue (an array of PCB structs) 
2.	The number of items in the ready queue
3.	the PCB of the currently running process 
4.	the PCB of the newly arriving process 
5.	the current timestamp. 

The method determines the process to execute next and returns its PCB. 
*/