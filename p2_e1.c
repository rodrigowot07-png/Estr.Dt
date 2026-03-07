#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "radio.h"
#include "stack.h"

int show_player_menu(Stack *history);

int show_player_menu(Stack *history) {
    int option;
    Music *m = NULL;
	
	/* Obtenemos canción actual del top de la pila */
	m = (Music *)stack_top (history);
    if (m != NULL) {
		music_formatted_print(stdout, m);
    } else {
        printf("\nNo song currently playing.\n");
    }
	
	/* Imprimimos historial (pila) */
	printf("\nRecently Played:\n");
	stack_print(stdout, history, music_plain_print);
	
	/* Mostramos menu y esperamos selección */
    printf("\n1. Back to previous song\n");
    printf("2. Exit\n");
    printf("Choose an option: ");

    scanf("%d", &option);

    return option;
}

/* TODO MAIN FUNCTION */
int main (int argc, char **argv) {
    FILE *fin = NULL;
    Radio *rad = NULL;
    Stack *stack = NULL;
    void *pop;
    Status stat;
    int pinput;

    if(argc < 2){
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }

    if(!(fin = fopen(argv[1], "r"))){
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }

    if (!(rad = radio_init())) {
        fprintf(stderr, "Error initializing the radio\n");
        return 1;
    }

    if(!(stack = stack_init())){
        radio_free(rad);
        return 1;
    }

    stat = radio_readFromFile(fin, rad, stack);
    if(stat == ERROR){
        fprintf(stderr, "Error reading the file\n");
        radio_free(rad);
        stack_free(stack);
        return 1;
    }

    do {
        pinput = show_player_menu(stack);

        if (pinput == 1) {
            pop = stack_pop(stack);
        }

        if (pop) {
            music_free(pop);
        }
        
    } while (pinput != 2);

    radio_free(rad);
    stack_free(stack);

    return 0;
}