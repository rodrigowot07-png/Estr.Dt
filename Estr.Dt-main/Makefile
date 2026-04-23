########################################################
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
EJS = p4_e1
########################################################
OBJECTSP4E1  = p4_e1.o radio.o music.o bstree.o queue.o stack.o
########################################################

all: $(EJS) clear

p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4E1)

p4_e1.o: p4_e1.c music.h radio.h bstree.h queue.h stack.h
	$(CC) $(CFLAGS) -c p4_e1.c

bstree.o: bstree.c bstree.h
	$(CC) $(CFLAGS) -c bstree.c

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
	@echo ">>>>>>Running p4_e1 normal"
	./p4_e1 data_music_10.txt 8 normal
	@echo ">>>>>>Running p4_e1 sorted"
	./p4_e1 data_music_10.txt 8 sorted
 
runv:
	@echo ">>>>>>Running p4_e1 normal with valgrind"
	valgrind --leak-check=full --track-origins=yes -s ./p4_e1 data_music_10.txt 8 normal
	@echo ">>>>>>Running p4_e1 sorted with valgrind"
	valgrind --leak-check=full --track-origins=yes -s ./p4_e1 data_music_10.txt 8 sorted