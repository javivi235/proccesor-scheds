#include <pthread.h>

#define TRUE 1
#define FALSE 0

typedef struct proceso proceso_t;

struct proceso
{
	int id;
	pthread_t *proceso;
	pthread_mutex_t mtx;
	int totalTime;
	int remainingTime;
	pthread_cond_t p_cond;
  	int cond;
	proceso_t *next;

};


typedef struct
{
	pthread_t *proceso;
	pthread_mutex_t mtx;
	pthread_cond_t p_cond;
  	int cond;	
}sched_t;

typedef struct
{
	proceso_t *proceso;
	sched_t *sched;
}instancia_t;

typedef struct
{
	proceso_t *ready;
	proceso_t *terminated;
	sched_t *sched;
	int lastID;

} data_t;

proceso_t * crearProceso();
void init (proceso_t *);
void *sched_hnd (void *);
void *process_hnd (void *);
void *moni_hnd (void *);
void sig_handler(int);
void initCurse();
void mostrarRuning (proceso_t *);
void mostrarReady (proceso_t *);
void mostrarTerminated (proceso_t *);
pthread_t * crearThread(proceso_t *);
void insertar_final (proceso_t **);
void insertar_inicio (data_t *);
