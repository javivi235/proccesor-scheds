#define TRUE 1
#define FALSE 0

#define CREATED 0
#define READY 1
#define RUNNING 2
#define WAIT 3
#define TERMINATED 4

typedef struct proceso proceso_t

struct proceso
{
	int id;
	pthread_t *proceso;
	pthread_mutex_t *mtx;
	int estado;
	int totalTime;
	int remainingTime;
	pthread_cond_t *p_cond;
  	int *cond;
	proceso_t *next;

};

void init (control_t[], pthread_mutex_t[], pthread_cond_t[], int[]);
void *sched_hnd (void *);
void *process_hnd (void *);
void *moni_hnd (void *);
void *principal_hnd(void *);

