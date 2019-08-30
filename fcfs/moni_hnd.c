#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include "procesos.h"

void *moni_hnd(void * arg)
{
	proceso_t **procesos = (proceso_t **) arg;

	initCurse();
	while (TRUE) 
	{
		clear();
		mostrarRuning(*procesos);
		mostrarReady(*procesos);
		mostrarTerminated(*procesos);
//		printf("moni: %d\n",*procesos);
		//if(*procesos!=NULL)		
		//printf("ID: %d\n", (*procesos)->id);	
	
		usleep(500000);
		refresh();
	}
	return NULL;
}

void
initCurse()
{
	initscr();
	start_color();

	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_GREEN, COLOR_BLUE);

	bkgd(COLOR_PAIR(1) | A_BOLD);
}

void mostrarRuning (proceso_t *procesos) 
{
	mvprintw(0, 0,"Runing:\n");
	mvprintw(2, 0,"ID:\n");
	mvprintw(2, 20,"TR:\n");
	int i = 2;
	proceso_t *next = procesos;
	while (next != NULL)
	{
		if (next->estado == RUNNING) 
		{
		mvprintw(2*i, 0,"%d\n", next->id);
		mvprintw(2*i, 20,"%d\n", next->remainingTime);
		}
		i++;
		next = next->next;
	}
}

void mostrarReady (proceso_t *procesos) 
{
	mvprintw(0, 40,"Ready:\n");
	mvprintw(2, 40,"ID:\n");
	mvprintw(2, 60,"TR:\n");
	int i = 2;
	proceso_t *next = procesos;
	while (next != NULL)
	{
		if (next->estado == READY) 
		{
		mvprintw(2*i, 40,"%d\n", next->id);
		mvprintw(2*i, 60,"%d\n", next->remainingTime);
		}
		i++;
		next = next->next;
	}
}

void mostrarTerminated (proceso_t *procesos) 
{
	mvprintw(0, 80,"Termitaed:\n");
	mvprintw(2, 80,"ID:\n");
	mvprintw(2, 100,"TR:\n");

	int i = 2;
	proceso_t *next = procesos;
	while (next != NULL)
	{
		if (next->estado == TERMINATED) 
		{
		mvprintw(2*i, 80,"%d\n", next->id);
		mvprintw(2*i, 100,"%d\n", next->remainingTime);
		}
		i++;
		next = next->next;
	}
}
