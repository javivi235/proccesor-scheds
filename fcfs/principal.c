#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "procesos.h"

data_t data;

int
main()
{
	data.ready = NULL;
	data.terminated = NULL;
	pthread_t sched;
	pthread_t monitor;
	pthread_create(&monitor, NULL, moni_hnd, (void *) &data);
	pthread_create (&sched, NULL, sched_hnd, (void *) &data);
	pthread_join(sched, NULL);
	signal (1, sig_handler);
}


void
sig_handler(int signo)
{
	proceso_t * proceso;
	
	switch(signo)
	{
	case 1:
	
	proceso = crearProceso();	
	init(proceso);
	insertar_final(&proceso);
	break;

	}
}

void
init (proceso_t * proceso)
{
	proceso->id = -1;
	proceso->totalTime = rand() %20;
	proceso->remainingTime = proceso->totalTime;
	proceso-> proceso= crearThread(proceso);
	proceso->cond = FALSE;
	
	proceso->mtx = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	proceso->p_cond = (pthread_cond_t)  PTHREAD_COND_INITIALIZER;
	proceso->next = NULL;
}

pthread_t * crearThread(proceso_t * proceso)
{
	pthread_t *hilo = (pthread_t *)malloc(sizeof(pthread_t));
	return hilo;
}

proceso_t * crearProceso()
{
	proceso_t *proceso = (proceso_t *)malloc(sizeof(proceso_t));
	init(proceso);	
	return proceso;
}

void
insertar_final (proceso_t **elem)
{
	proceso_t **proceso;
	proceso = &(data.ready);
	int i = 0;
	while(*proceso != NULL)
	{
		proceso = &((*proceso)->next);	
		i++;	
	}
	*proceso = *elem;
	((*proceso)->id) = i;
}



