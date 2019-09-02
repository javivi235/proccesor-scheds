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

			pthread_mutex_lock(&((data->sched)->mtx));
			if ((data->sched)->cond)
			{
				ordenar_procesos(data);
				instancia_t ins;
				ins.proceso = data->ready;
				ins.sched = data->sched;
				pthread_create(((data->ready)->proceso), NULL, process_hnd, (void *)(&ins));
				(data->ready)->cond = 1;
				(data->sched)->cond = FALSE;
				pthread_cond_wait(&((data->sched)->p_cond), &((data->sched)->mtx));
				(data->sched)->cond = TRUE;
				if ((data->ready)->remainingTime == 0)
				{	
					insertar_inicio(data);
				}
			
			}
			pthread_mutex_unlock(&((data->sched)->mtx));

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

void
ordenar_procesos (data_t *data)
{
	proceso_t **A;
	proceso_t **B;
	proceso_t **C;

	if ((data->ready) != NULL && (data->ready)->next != NULL)
	{
		A = &(data->ready);
		B = &((*A)->next);
		C =  &((*B)->next);
		proceso_t *aux;
		while (*A != NULL && *B != NULL)
		{
			if ((*A)->remainingTime > (*B)->remainingTime)
			{
				aux = *A;
				*A = *B;
				*B = *C;
				*C = aux;

				A = &(data->ready);
				B = &((*A)->next);
				C = &((*B)->next);
			} else {
				A = B;
				B = C;
				C = &((*C)->next);
			}		
		}
	}
}
void
tryToShift(proceso_t **procesoAnt, proceso_t **proceso, proceso_t **procesoSig)
{

}
