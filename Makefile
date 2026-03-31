########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p3_e1 p3_e2
########################################################
OBJECTSP3E1 = p3_e1.o radio.o music.o queue.o stack.o
OBJECTSP3E2 = p3_e2.o radio.o music.o queue.o stack.o
########################################################

all: $(EJS) clear


p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

p3_e2: $(OBJECTSP3E2)
	$(CC) $(CFLAGS) -o p3_e2 $(OBJECTSP3E2)


p3_e1.o: p3_e1.c music.h radio.h queue.h stack.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2.o: p3_e2.c music.h radio.h queue.h stack.h
	$(CC) $(CFLAGS) -c p3_e2.c


music.o: music.c music.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h queue.h stack.h
	$(CC) $(CFLAGS) -c radio.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS) p3_e1 p3_e2

	
run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 playlist1.txt
	@echo ">>>>>>Running p3_e2"
	./p3_e2 radio_bfs.txt 1 2

runv:
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e1 playlist1.txt
	@echo ">>>>>>Running p3_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e2 radio_bfs.txt 1 2