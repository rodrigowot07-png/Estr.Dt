########################################################
CC=gcc
CFLAGS= -g -Wall
EJS = p2_e2b
########################################################
OBJECTSP1E1 = p1_e1.o music.o
OBJECTSP1E2 = p1_e2.o radio.o music.o
OBJECTSP1E3 = p1_e3.o radio.o music.o
OBJECTSP2E1 = p2_e1.o radio.o music.o
OBJECTSP2E2A = p2_e2a.o radio.o music.o
OBJECTSP2E2B = p2_e2b.o radio.o music.o
########################################################

all: $(EJS) clear

p1_e1: $(OBJECTSP1E1)
	$(CC) $(CFLAGS) -o p1_e1 $(OBJECTSP1E1)

p1_e2: $(OBJECTSP1E2)
	$(CC) $(CFLAGS) -o p1_e2 $(OBJECTSP1E2)

p1_e3: $(OBJECTSP1E3)
	$(CC) $(CFLAGS) -o p1_e3 $(OBJECTSP1E3)

p2_e1: $(OBJECTSP2E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2E1) -L. -lstack

p2_e2a: $(OBJECTSP2E2A)
	$(CC) $(CFLAGS) -o p2_e2a $(OBJECTSP2E2A) -L. -lstack	

p2_e2b: $(OBJECTSP2E2B)
	$(CC) $(CFLAGS) -o p2_e2b $(OBJECTSP2E2B) -L. -lstack	

#p1_e1.o: p1_e1.c music.h
#	$(CC) $(CFLAGS) -c p1_e1.c

#p1_e2.o: p1_e2.c music.h radio.h
#	$(CC) $(CFLAGS) -c p1_e2.c
	
#p1_e3.o: p1_e3.c music.h radio.h
#	$(CC) $(CFLAGS) -c p1_e3.c

#p2_e1.o: p2_e1.c music.h radio.h
#	$(CC) $(CFLAGS) -c p2_e1.c

#p2_e2a.o: p2_e2a.c music.h radio.h
#	$(CC) $(CFLAGS) -c p2_e2a.c

p2_e2b.o: p2_e2b.c music.h radio.h
	$(CC) $(CFLAGS) -c p2_e2b.c

music.o: music.c music.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run_e2b:
	@echo ">>>>>>Running p2_e2b with playlistA and playlistB"
	./p2_e2b playlistA.txt playlistB.txt

runv_e2b:
	@echo ">>>>>>Running p2_e2b with valgrind"
	valgrind --leak-check=full ./p2_e2b playlistA.txt playlistB.txt
		
run:
	@echo ">>>>>>Running p2_e1"
	./p2_e1 playlist1.txt
	@echo ">>>>>>Running p2_e2a with playlistA and playlistB"
	./p2_e2a playlist1.txt playlist2.txt

runv:
	@echo ">>>>>>Running p2_e1 with valgrind"
	valgrind --leak-check=full ./p2_e1
	@echo ">>>>>>Running p2_e2a with valgrind"
	valgrind --leak-check=full ./p2_e2a playlist1.txt playlist2.txt
