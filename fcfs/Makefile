CC = gcc
IDIR = .
CFLAGS = -I$(IDIR) -std=gnu99
LIBS = -lpthread -lncurses
OBJ = principal.c sched_hnd.c moni_hnd.c process_hnd.c
DEPS = procesos.h

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)


procsched: $(OBJ) 
	$(CC) -Wall -o $@ $^ $(CFLAGS) $(LIBS)

# clean out the dross
clean:
	rm -f procsched  *~ *.o 
