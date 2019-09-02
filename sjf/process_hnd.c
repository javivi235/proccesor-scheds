#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "procesos.h"


void *process_hnd(void * arg)
{
	instancia_t *ins = (instancia_t *) arg;
	signal(1,sig_handler);
	while (TRUE) 
	{
		pthread_mutex_lock(&((ins->proceso)->mtx));
		if ((ins->proceso)->cond)
		{
			while ((ins->proceso)->remainingTime > 0)
			{
			(ins->proceso)->remainingTime = (ins->proceso)->remainingTime -1;		
			usleep(1000000);				
			}
			(ins->proceso)->cond = FALSE;
			pthread_cond_signal(&((ins->sched)->p_cond));
			
		}
		pthread_mutex_unlock(&((ins->proceso)->mtx));
		
		break;
	}
	return NULL;
}