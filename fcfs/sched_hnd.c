#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "procesos.h"

void *sched_hnd(void * arg)
{
	data_t *data = (data_t *) arg;
	signal(1,sig_handler);
	while (TRUE) 
	{
		if (data->ready != NULL)
		{
			if ((data->ready)->remainingTime == (data->ready)->totalTime)
			{
			(data->ready)->cond = TRUE;
			pthread_create(((data->ready)->proceso), NULL, process_hnd, (void *)(data->ready));			
			} else if ((data->ready)->remainingTime ==0) 
			{
				(data->ready)->cond = FALSE;
				insertar_inicio(data);
			}
		}
	}
	return NULL;
}

void
insertar_inicio (data_t *data)
{		
	proceso_t *next = data->ready;
	(data->ready)= (data->ready)->next;
	next->next = data->terminated;
	data->terminated = next;
}
