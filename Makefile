########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p2_e1 p2_e2a p2_e2b p2_e3 p2_e1s p2_e2as p2_e2bs p2_e3s
########################################################
OBJECTSP2E1 = p2_e1.o radio.o music.o
OBJECTSP2E2A = p2_e2a.o radio.o music.o
OBJECTSP2E2B = p2_e2b.o radio.o music.o
OBJECTSP2E3 = p2_e3.o radio.o music.o

OBJECTSP2E1S = p2_e1s.o radio.o music.o stack.o
OBJECTSP2E2AS = p2_e2as.o radio.o music.o stack.o
OBJECTSP2E2BS = p2_e2bs.o radio.o music.o stack.o
OBJECTSP2E3S = p2_e3s.o radio.o music.o stack.o
########################################################

all: $(EJS) clear

p2_e1: $(OBJECTSP2E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2E1) -L. -lstack

p2_e2a: $(OBJECTSP2E2A)
	$(CC) $(CFLAGS) -o p2_e2a $(OBJECTSP2E2A) -L. -lstack	

p2_e2b: $(OBJECTSP2E2B)
	$(CC) $(CFLAGS) -o p2_e2b $(OBJECTSP2E2B) -L. -lstack	

p2_e3: $(OBJECTSP2E3)
	$(CC) $(CFLAGS) -o p2_e3 $(OBJECTSP2E3) -L. -lstack


p2_e1s: $(OBJECTSP2E1S)
	$(CC) $(CFLAGS) -o p2_e1s $(OBJECTSP2E1S)

p2_e2as: $(OBJECTSP2E2AS)
	$(CC) $(CFLAGS) -o p2_e2as $(OBJECTSP2E2AS)

p2_e2bs: $(OBJECTSP2E2BS)
	$(CC) $(CFLAGS) -o p2_e2bs $(OBJECTSP2E2BS)	

p2_e3s: $(OBJECTSP2E3S)
	$(CC) $(CFLAGS) -o p2_e3s $(OBJECTSP2E3S)


p2_e1.o: p2_e1.c music.h radio.h
	$(CC) $(CFLAGS) -c p2_e1.c

p2_e2a.o: p2_e2a.c music.h radio.h
	$(CC) $(CFLAGS) -c p2_e2a.c

p2_e2b.o: p2_e2b.c music.h radio.h
	$(CC) $(CFLAGS) -c p2_e2b.c

p2_e3.o: p2_e3.c music.h radio.h
	$(CC) $(CFLAGS) -c p2_e3.c


p2_e1s.o: p2_e1s.c music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p2_e1s.c

p2_e2as.o: p2_e2as.c music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p2_e2as.c

p2_e2bs.o: p2_e2bs.c music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p2_e2bs.c

p2_e3s.o: p2_e3s.c music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p2_e3s.c


music.o: music.c music.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS) p2_e1 p2_e2a p2_e2b p2_e3

	
runp2:
	@echo ">>>>>>Running p2_e1"
	./p2_e1 playlist1.txt
	@echo ">>>>>>Running p2_e2a with playlist1 and playlist2"
	./p2_e2a playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e2b with playlistA and playlistB"
	./p2_e2b playlistA.txt playlistB.txt
	@echo ">>>>>>Running p2_e3 (from id:1 to id:9)"
	./p2_e3 radio_dfs.txt 1 9
	@echo ">>>>>>Running p2_e1s"
	./p2_e1s playlist1.txt
	@echo ">>>>>>Running p2_e2as with playlist1 and playlist2"
	./p2_e2as playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e2bs with playlistA and playlistB"
	./p2_e2bs playlistA.txt playlistB.txt
	@echo ">>>>>>Running p2_e3s (from id:1 to id:9)"
	./p2_e3s radio_dfs.txt 1 9

runvp2:
	@echo ">>>>>>Running p2_e1 with valgrind"
	valgrind --leak-check=full ./p2_e1 playlist1.txt
	@echo ">>>>>>Running p2_e2a with valgrind"
	valgrind --leak-check=full ./p2_e2a playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e2b with valgrind"
	valgrind --leak-check=full ./p2_e2b playlistA.txt playlistB.txt
	@echo ">>>>>>Running p2_e3 with valgrind"
	valgrind --leak-check=full ./p2_e3 radio_dfs.txt 1 9
	@echo ">>>>>>Running p2_e1s with valgrind"
	valgrind --leak-check=full ./p2_e1s playlist1.txt
	@echo ">>>>>>Running p2_e2as with valgrind"
	valgrind --leak-check=full ./p2_e2as playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e2bs with valgrind"
	valgrind --leak-check=full ./p2_e2bs playlistA.txt playlistB.txt
	@echo ">>>>>>Running p2_e3s with valgrind"
	valgrind --leak-check=full ./p2_e3s radio_dfs.txt 1 9