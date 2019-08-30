#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "procesos.h"

void *sched_hnd(void * arg)
{
	proceso_t **procesos = (proceso_t **) arg;
	signal(1,sig_handler);
	while (TRUE) 
	{
		//printf("bbcita\n");
	}
	return NULL;
}
