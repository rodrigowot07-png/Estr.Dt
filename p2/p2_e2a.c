#include <stdlib.h>
#include <stdio.h>

#include "radio.h"
#include "stack.h"

Status merge_stacks(Stack *stin1, Stack *stin2, Stack *stout) {
    Music *m1 = NULL;
    Music *m2 = NULL;
    void *e = NULL;
    Stack *s = NULL;

    if (!stin1 || !stin2 || !stout) {
        return ERROR;
    }

    while (stack_isEmpty(stin1) == FALSE && stack_isEmpty(stin2) == FALSE) {
        m1 = (Music *)stack_top(stin1);
        m2 = (Music *)stack_top(stin2);

        if (music_getDuration(m1) > music_getDuration(m2)) {
            e = stack_pop(stin1);
        } else {
            e = stack_pop(stin2);
        }

        if (stack_push(stout, e) == ERROR) {
            return ERROR;
        }
    }

    s = (stack_isEmpty(stin1) == TRUE) ? stin2 : stin1;

    while (stack_isEmpty(s) == FALSE) {
        e = stack_pop(s);

        if (stack_push(stout, e) == ERROR) {
            return ERROR;
        }
    }

    return OK;
}

int main(int argc, char *argv[]) {
    FILE *f1 = NULL, *f2 = NULL;
    Radio *r1 = NULL, *r2 = NULL;
    Stack *s1 = NULL, *s2 = NULL, *sout = NULL;

    if (argc < 3) {
        fprintf(stderr, "Error, use: %s <playlistA.txt> <playlistB.txt>\n", argv[0]);
        return 1;
    }

    r1 = radio_init();
    if (r1 == NULL) { 
        printf("DEBUG: Error in r1 (radio_init)\n"); 
        return 1; 
    }
    
    r2 = radio_init();
    if (r2 == NULL) { 
        printf("DEBUG: Error in r2 (radio_init)\n"); 
        return 1; 
    }
    
    s1 = stack_init();
    if (s1 == NULL) { 
        printf("DEBUG: Error in s1 (stack_init)\n"); 
        return 1; 
    }
    
    s2 = stack_init();
    if (s2 == NULL) { 
        printf("DEBUG: Error in s2 (stack_init)\n"); 
        return 1; 
    }
    
    sout = stack_init();
    if (sout == NULL) { 
        printf("DEBUG: Error in sout (stack_init)\n"); 
        return 1; 
    }

    if (!(f1 = fopen(argv[1], "r"))) {
        fprintf(stderr, "Error opening %s\n", argv[1]);
    } else {
        radio_readFromFile(f1, r1, s1);
        fclose(f1);
    }

    if (!(f2 = fopen(argv[2], "r"))) {
        fprintf(stderr, "Error opening %s\n", argv[2]);
    } else {
        radio_readFromFile(f2, r2, s2);
        fclose(f2);
    }

    printf("Playlist 0:\n");
    stack_print(stdout, s1, music_plain_print);

    printf("Playlist 1:\n");
    stack_print(stdout, s2, music_plain_print);

    if (merge_stacks(s1, s2, sout) == OK) {
        fprintf(stdout, "\nPlaylist combined:\n");
        stack_print(stdout, sout, music_plain_print);
        printf("\n");
    } else {
        fprintf(stderr, "Error combining playlists\n");
    }

    radio_free(r1);
    radio_free(r2);
    stack_free(s1);
    stack_free(s2);
    stack_free(sout);

    return 0;
}