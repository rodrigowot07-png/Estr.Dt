########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p3_e1 p3_e2 p3_e3 p3_e1s p3_e2s
########################################################
OBJECTSP3E1  = p3_e1.o radio.o music.o queue.o stack.o
OBJECTSP3E2  = p3_e2.o radio.o music.o queue.o stack.o
OBJECTSP3E3  = p3_e3.o music.o list.o
OBJECTSP3E1S = p3_e1.o radio.o music.o queueList.o list.o stack.o
OBJECTSP3E2S = p3_e2.o radio.o music.o queueList.o list.o stack.o
########################################################

all: $(EJS) clear


p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

p3_e2: $(OBJECTSP3E2)
	$(CC) $(CFLAGS) -o p3_e2 $(OBJECTSP3E2)

p3_e3: $(OBJECTSP3E3)
	$(CC) $(CFLAGS) -o p3_e3 $(OBJECTSP3E3)

p3_e1s: $(OBJECTSP3E1S)
	$(CC) $(CFLAGS) -o p3_e1s $(OBJECTSP3E1S)

p3_e2s: $(OBJECTSP3E2S)
	$(CC) $(CFLAGS) -o p3_e2s $(OBJECTSP3E2S)


p3_e1.o: p3_e1.c music.h radio.h queue.h stack.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2.o: p3_e2.c music.h radio.h queue.h stack.h
	$(CC) $(CFLAGS) -c p3_e2.c

p3_e3.o: p3_e3.c music.h list.h
	$(CC) $(CFLAGS) -c p3_e3.c

p3_e1s.o: p3_e1s.c radio.h music.h types.h stack.h queue.h
	$(CC) $(CFLAGS) -c p3_e1s.c

p3_e2s.o: p3_e2s.c music.h types.h radio.h stack.h queue.h
	$(CC) $(CFLAGS) -c p3_e2s.c


music.o: music.c music.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h queue.h stack.h
	$(CC) $(CFLAGS) -c radio.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

queueList.o: queueList.c queue.h list.h
	$(CC) $(CFLAGS) -c queueList.c

clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 playlist1.txt
	@echo ">>>>>>Running p3_e2"
	./p3_e2 radio_bfs.txt 1 2
	@echo ">>>>>>Running p3_e3"
	./p3_e3 radio_bfs.txt
	@echo ">>>>>>Running p3_e1s"
	./p3_e1s playlist1.txt
	@echo ">>>>>>Running p3_e2s"
	./p3_e2s radio_bfs.txt 1 2

runv:
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e1 playlist1.txt
	@echo ">>>>>>Running p3_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e2 radio_bfs.txt 1 2
	@echo ">>>>>>Running p3_e3 with valgrind"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e3 radio_bfs.txt
	@echo ">>>>>>Running p3_e1s with valgrind"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e1s playlist1.txt
	@echo ">>>>>>Running p3_e2s with valgrind"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e2s radio_bfs.txt 1 2