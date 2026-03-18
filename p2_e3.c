#include <stdio.h>
#include <stdlib.h>

#include "music.h"
#include "radio.h"
#include "stack.h"

int main(int argc, char *argv[]) {
    Radio *r   = NULL;
    Stack *s   = NULL;   
    FILE  *fin = NULL;
    long   from_id, to_id;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <radio_file> <from_id> <to_id>\n", argv[0]);
        return 1;
    }

    from_id = atol(argv[2]);
    to_id   = atol(argv[3]);

    if (!(fin = fopen(argv[1], "r"))) {
        fprintf(stderr, "Error, could not open file %s\n", argv[1]);
        return 1;
    }

    if (!(r = radio_init())) {
        fclose(fin);
        return 1;
    }

    if (!(s = stack_init())) {
        radio_free(r);
        fclose(fin);
        return 1;
    }

    if (radio_readFromFile(fin, r, s) == ERROR) {
        fprintf(stderr, "Error: could not read songs from %s\n", argv[1]);
        stack_free(s);
        radio_free(r);
        fclose(fin);
        return 1;
    }

    if (radio_readRelationsFromFile(fin, r) == ERROR) {
        fprintf(stderr, "Error: could not read relations from '%s'\n", argv[1]);
        stack_free(s);
        radio_free(r);
        fclose(fin);
        return 1;
    }

    fclose(fin);

    printf("Radio:\n");
    radio_print(stdout, r);
    printf("\n");

    printf("From music with id: %ld\n", from_id);
    printf("To music with id: %ld\n",   to_id);
    printf("Music exploration path:\n");

    if (radio_depthSearch(r, from_id, to_id) == ERROR) {
        fprintf(stderr, "Error: DFS failed.\n");
        stack_free(s);
        radio_free(r);
        return 1;
    }

    stack_free(s);
    radio_free(r);

    return 0;
}