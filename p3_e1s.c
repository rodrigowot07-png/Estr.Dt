#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "radio.h"
#include "queue.h"

int show_player_menu(Queue *history);

int show_player_menu(Queue *history) {
    int option = 0;
    Music *m = NULL;
	
	/* Obtenemos canción actual del front de la lista */
	m = (Music *)queue_getFront(history);
    if (m != NULL) {
		music_formatted_print(stdout, m);
    } else {
        printf("\nNo song currently playing.\n");
    }
	
	/* Imprimimos historial (cola) */
	printf("\nUpcoming:\n");
	queue_print(stdout, history, music_plain_print);
	
	/* Mostramos menu y esperamos selección */
    do {
        printf("1. Next song\n");
        printf("2. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid option\n");
            while (getchar() != '\n');
            option = -1;
            continue;
        }

        if (option != 1 && option != 2) {
            printf("No option available\n");
        }

    } while (option != 1 && option != 2);

    return option;
}

/* TODO MAIN FUNCTION */
int main (int argc, char *argv[]) {
    FILE *fin = NULL;
    Radio *rad = NULL;
    Queue *queue = NULL;
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

    if(!(queue = queue_new())){
        radio_free(rad);
        return 1;
    }

    stat = radio_readFromFile(fin, rad, queue);
    if(stat == ERROR){
        fprintf(stderr, "Error reading the file\n");
        radio_free(rad);
        queue_free(queue);
        return 1;
    }

    do {
        pinput = show_player_menu(queue);

        if (pinput == 1) {
            queue_pop(queue);
        }
        
    } while (pinput != 2);

    radio_free(rad);
    queue_free(queue);
    fclose(fin);

    return 0;
}