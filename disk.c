#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "oslabs.h"

/*
	struct RCB {
        int request_id;
        int arrival_timestamp;
        int cylinder;
        int address;
        int process_id;
    };
*/

int is_NULLrcb(struct RCB inrcb)
{
    if(inrcb.request_id == 0 && inrcb.arrival_timestamp == 0 && inrcb.cylinder == 0 && inrcb.address == 0 &&	inrcb.process_id ==
    0)
    return 1;
    else
        return 0;    
}

struct RCB null_rcb = {0,0,0,0,0};

/****************************************************************************************************************************************************************/

struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp)

{
	if(is_NULLrcb(current_request))
	{
		return new_request;
	}
	else
		request_queue[*queue_cnt] = new_request;
		(*queue_cnt) = (*queue_cnt) + 1;
		return current_request;
}

/******************************************************************************************************************************************************************/

struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp)

{
	if(is_NULLrcb(current_request))
	{
		return new_request;
	}
	else
		request_queue[*queue_cnt] = new_request;
		(*queue_cnt) = (*queue_cnt) + 1;
		return current_request;
}

/******************************************************************************************************************************************************************/

struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp)
{
	if(is_NULLrcb(current_request))
	{
		return new_request;
	}
	else
		request_queue[*queue_cnt] = new_request;
		(*queue_cnt) = (*queue_cnt) + 1;
		return current_request;
}

/******************************************************************************************************************************************************************/

struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],int *queue_cnt)
{
	if(*queue_cnt == 0)
		return null_rcb;
	
	int earliest_arrival = 0;
	
	for (int i = 1; i < *queue_cnt; i++)
	{
		if (request_queue[i].arrival_timestamp < request_queue[earliest_arrival].arrival_timestamp)
		{
			earliest_arrival = i;
		}
	}
	struct RCB remove_me_from_queue_and_return = request_queue[earliest_arrival];
	for (int i = earliest_arrival -1; i < *queue_cnt - 1; i++)
	{
		request_queue[i] = request_queue[i+1];
	}
	(*queue_cnt) = (*queue_cnt) - 1;
	return remove_me_from_queue_and_return;	
}

/******************************************************************************************************************************************************************/

struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt,int current_cylinder)
{
	if(*queue_cnt == 0)
		return null_rcb;
	
	struct relative_closeness_request
	{
		struct RCB rcb_in_queue;
		int distance_from_cylinder;
		int close_cylinder;
	};
	
	struct relative_closeness_request rcq[*queue_cnt];
	
	int closest_request;
	
	for (int i = 0; i < *queue_cnt; i++)
	{
		rcq[i].rcb_in_queue = request_queue[i];
		rcq[i].close_cylinder = 0;
		
		rcq[i].distance_from_cylinder = (request_queue[i].cylinder - current_cylinder) * (request_queue[i].cylinder - current_cylinder);
		if (i == 0)
			closest_request = rcq[i].distance_from_cylinder;
		else if (closest_request > rcq[i].distance_from_cylinder)
			closest_request = rcq[i].distance_from_cylinder;
	}
	for (int i = 0; i < *queue_cnt; i++)
	{
		if (rcq[i].distance_from_cylinder == closest_request)
			rcq[i].close_cylinder = 1;
	}
	
	
	// of the rcb's marked as requesting closest, determine which arrived first
	int first_request = 1;
	struct RCB this_is_the_next_rcb;
	int next_rcb_index;
	
	for (int i = 0; i < *queue_cnt; i++)
	{
		if(first_request == 1 && rcq[i].close_cylinder == 1)
		{
			this_is_the_next_rcb = rcq[i].rcb_in_queue;
			first_request = 0;
			next_rcb_index = i;
		}
		else if (rcq[i].close_cylinder == 1 && rcq[i].rcb_in_queue.arrival_timestamp < this_is_the_next_rcb.arrival_timestamp)
		{
			this_is_the_next_rcb = rcq[i].rcb_in_queue;
			next_rcb_index = i;
		}
		
		for (int i = next_rcb_index; i < *queue_cnt - 1; i++)
		{
			request_queue[i] = request_queue[i+1];
		}
	}
	*queue_cnt = *queue_cnt - 1;
	return this_is_the_next_rcb;
}

/******************************************************************************************************************************************************************/

struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, int current_cylinder, int scan_direction)
{
	if(*queue_cnt == 0)
		return null_rcb;
	
	int earliest_time = 1000;
	int early_index = 0;
	
	for (int i = 0; i < *queue_cnt; i++)
	{
		if(request_queue[i].cylinder == current_cylinder)
		{
			if(request_queue[i].arrival_timestamp < earliest_time)
			{
				earliest_time = request_queue[i].arrival_timestamp;
				early_index = i;
			}
		}
	}
	
	if (earliest_time != 1000)
	{
		struct RCB result = request_queue[early_index];
		
		request_queue[early_index] = request_queue[(*queue_cnt) - 1];
		(*queue_cnt)--;
		
		return result;
	}
	
	int closest = 1000;
	int closest_index = 0;
	
	if (scan_direction == 1)
	{
		for (int i = 0; i < *queue_cnt; i++)
		{
			if(request_queue[i].cylinder > current_cylinder)
			{
				if(abs(request_queue[i].cylinder - current_cylinder) < closest)
				{
					closest = abs(request_queue[i].cylinder - current_cylinder);
					closest_index = i;
				}
			}
		}
		
		if (closest != 1000)
		{
			struct RCB result = request_queue[closest_index];
			
			request_queue[closest_index] = request_queue[(*queue_cnt) -1];
			(*queue_cnt)--;
			
			return result;
		}
		
		closest = 1000;
		closest_index = 0;
		
		for (int i = 0; i < *queue_cnt; i++)
		{
			if(abs(request_queue[i].cylinder - current_cylinder) < closest)
			{
				closest = abs(request_queue[i].cylinder - current_cylinder);
				closest_index = i;
			}
		}
		struct RCB result = request_queue[early_index];
		request_queue[early_index] = request_queue[(*queue_cnt) - 1];
		(*queue_cnt)--;
		
		return result;
		
	}
	
	if (scan_direction == 0)
	{
		for (int i = 0; i < *queue_cnt; i++)
		{
			if(request_queue[i].cylinder < current_cylinder)
			{
				if(abs(request_queue[i].cylinder < current_cylinder))
				{
					closest = abs(request_queue[i].cylinder - current_cylinder);
					closest_index = i;
				}
			}
		}
		
		if (closest != 1000)
		{
			struct RCB result = request_queue[closest_index];
			
			request_queue[closest_index] = request_queue[(*queue_cnt) - 1];
			(*queue_cnt)--;
			
			return result;
		}
		
		for (int i = 0; i < *queue_cnt; i++)
		{
			if(abs(request_queue[i].cylinder - current_cylinder) < closest)
			{
				closest = abs(request_queue[i].cylinder - current_cylinder);
				closest_index = i;
			}
		}
		
		struct RCB result = request_queue[early_index];
		request_queue[early_index] = request_queue[(*queue_cnt) - 1];
		(*queue_cnt)--;
		
		return result;
	}
		
}