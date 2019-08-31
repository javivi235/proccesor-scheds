#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include <signal.h>
#include "procesos.h"

void *moni_hnd(void * arg)
{
	data_t *data = (data_t *) arg;
	signal(1,sig_handler);
	initCurse();
	while (TRUE) 
	{
		clear();
		mostrarRuning(data->ready);
		mostrarReady(data->ready);
		mostrarTerminated(data->terminated);
	
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
	mvprintw(2, 10,"TR:\n");
	proceso_t *next = procesos;
	if (next != NULL)
	{
		
		mvprintw(4, 0,"%d\n", next->id);
		mvprintw(4, 10,"%d\n", next->remainingTime);
		
	}
}

void mostrarReady (proceso_t *procesos) 
{
	mvprintw(0, 30,"Ready:\n");
	mvprintw(2, 30,"ID:\n");
	mvprintw(2, 40,"TR:\n");
	int i = 1;
	proceso_t *next = procesos;
	while (next != NULL)
	{
		if (i>1) 
		{
		mvprintw(2*i, 30,"%d\n", next->id);
		mvprintw(2*i, 40,"%d\n", next->remainingTime);
		}
		i++;
		next = next->next;
	}
}

void mostrarTerminated (proceso_t *procesos) 
{
	mvprintw(0, 60,"Termitaed:\n");
	mvprintw(2, 60,"ID:\n");
	mvprintw(2, 70,"TR:\n");
	
	int i = 2;
	proceso_t *next = procesos;
	while (next != NULL)
	{
		mvprintw(2*i, 60,"%d\n", next->id);
		mvprintw(2*i, 70,"%d\n", next->remainingTime);
		i++;
		next = next->next;
	}
}
