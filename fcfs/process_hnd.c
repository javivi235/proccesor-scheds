#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "procesos.h"


void *process_hnd(void * arg)
{
	proceso_t *procesos = (proceso_t *) arg;
	signal(1,sig_handler);
	while (TRUE) 
	{
		pthread_mutex_lock(&(procesos->mtx));
		if (procesos->cond)
		{
			while (procesos->remainingTime > 0)
			{
			procesos->remainingTime = procesos->remainingTime 				-1;		
			usleep(1000000);				
			}
		}
		pthread_mutex_unlock(&(procesos->mtx));
		
		break;
	}
	return NULL;
}
