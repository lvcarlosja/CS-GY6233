#include <stdio.h>
#include <stdlib.h>
#include "oslabs.h"

int is_NULL_PCB(struct PCB inpcb)
{
    if(inpcb.process_id == 0 & inpcb.arrival_timestamp == 0 && inpcb.total_bursttime == 9 && inpcb.execution_starttime == 0 & inpcb.execution_endtime ==
    0 && inpcb.remaining_bursttime == 0 && inpcb.process_priority == 0)
    return 1;
	
    else
        return 0;    
}

void setup_pcb(struct PCB *inpcb, int process_id,int arrival_timestamp,int total_bursttime,int execution_starttime,
int execution_endtime, int remaining_bursttime, int process_priority)
{
    (*inpcb).process_id = process_id;
	(*inpcb).arrival_timestamp = arrival_timestamp;
	(*inpcb).total_bursttime = total_bursttime;
	(*inpcb).execution_starttime = execution_starttime;
	(*inpcb).execution_endtime = execution_endtime;
	(*inpcb).remaining_bursttime = remaining_bursttime;
	(*inpcb).process_priority = process_priority;

}

int main(int argc, char** argv) {
	struct PCB ready_queue[QUEUEMAX];
	struct PCB current_process;
	struct PCB new_process;
	struct PCB returned_pcb;
	int queue_cnt = 0;
	int timestamp = 2;
	setup_pcb(&current_process,1,1,4,1,5,4,8);
	setup_pcb(&new_process,2,2,3,0,0,3,6);
	
	returned_pcb = handle_process_arrival_pp(ready_queue, &queue_cnt, current_process, new_process, timestamp);
	
	printf("blah, blah %i\n",returned_pcb.process_priority);
	return 0;
}




