/**
 * @file radio.c
 * @author Nicolas Encinas y Rodrigo Martin
 * @date February 2026
 * @mersion 1.0
 * @brief Library to manage ADT Music
 *
 * @details 
 * 
 * @see
 */

#include <stdio.h>
#include <stdlib.h>


#include "radio.h"


#define STR_LENGTH 64


struct _Radio {
    Music *songs[MAX_MSC];
    Bool relations[MAX_MSC][MAX_MSC];
    int num_music;
    int num_relations;
};

/* Private function */
int radio_findId(const Radio *r, long id) {
    int i;

    /*Control error*/
    if (!r) {
        return -1;
    }

    /* Finds the id of the music stored in the *songs array */
    for (i = 0; i < r->num_music; i++) {
        if (music_getId(r->songs[i]) == id) {
            return i;
        }
    }

    return -1;
}

Radio * radio_init() {
    Radio *r = NULL;
    int i, j;

    /* Allocates memory for the Radio struct */
    if (!(r = (Radio *) calloc (1, sizeof(Radio)))) {
        return  NULL;
    }

    /* Initializes the number of musics and relations */
    r->num_music = 0;
    r->num_relations = 0;

    /* Initializes the songs and the relations to FALSE */
    for (i = 0; i < MAX_MSC; i++) {
        for (j = 0; j < MAX_MSC; j++) {
            r->relations[i][j] = FALSE;
        }

        r->songs[i] = NULL; 
    }

    return r;
}

void radio_free(Radio *r) {
    int i;

    /* Control error */
    if (!r) {
        return;
    }

    /* Clears the songs */
    for (i = 0; i < r->num_music; i++) {
        music_free(r->songs[i]);
    }

    /* Clears the Radio struct */
    free(r);
}

Status radio_newMusic(Radio *r, char *desc) {
    Music *m = NULL;
    long id;
    int index = 0;

    /* Control error */
    if (!r || !desc) {
        return ERROR;
    }

    if (!(m = music_initFromString(desc))) {
        return ERROR;
    }

    id = music_getId(m);

    /* If the music already exixts, it is not added */
    if (radio_contains(r, id)) {
        music_free(m);
        return OK;
    }

    /* Checks that there is space in order to add more musics */
    if (r->num_music > MAX_MSC) {
        music_free(m);
        return ERROR;
    }

    if ((index = radio_getNumberOfMusic(r)) == -1) {
        return ERROR;
    }

    if(music_setIndex(m, index) == ERROR) {
        return ERROR;
    }

    /* Adds the new music to *songs in the last position of the  array */
    r->songs[r->num_music++] = m;

    return OK;
}

Status radio_newRelation(Radio *r, long orig, long dest) {
    long i, j;

    if (!r) {
        return ERROR;
    }

    /* Searches for the orig id */
    for(i=0; i < r->num_music; i++){
        if(music_getId(r->songs[i]) == orig){
            break;
        }

        if(i == r->num_music){
            return ERROR;
        }
    }

    /* Searches for the dest id */
    for(j=0; j< r->num_music; j++){
        if(music_getId(r->songs[j]) == dest){
            break;
        }

        if(j == r->num_music){
            return ERROR;
        }
    }

    /* Creates the relation */
    if (!r->relations[i][j]) {
        r->relations[i][j] = TRUE;
        r->num_relations++;
    }

    return OK;
}

Bool radio_contains(const Radio *r, long id) {
    if (!r) {
        return FALSE;
    }

    if (radio_findId(r, id) != -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int radio_getNumberOfMusic(const Radio *r){
    if(!r){
        return -1;
    }
    
    return r->num_music;
}

int radio_getNumberOfRelations(const Radio *r){
    if(!r){
        return -1;
    }
    
    return r->num_relations;
}

Bool radio_relationExists(const Radio *r, long orig, long dest){
    long i, j;

    /* Control error */
    if(!r){
        return FALSE;
    }

    /* Finds the id of the two musics */
    i = radio_findId(r, orig);
    j = radio_findId(r, dest);

    /* Checks if the id of both musics were found */
    if (i == -1 || j == -1) {
        return FALSE;
    }

    return r->relations[i][j];
}

int radio_getNumberOfRelationsFromId(const Radio *r, long id) {
    int counter = 0;
    int i, j;

    /* Control error */
    if (!r) {
        return -1;
    }

    i = radio_findId(r, id);

    if (i == -1) {
        return -1;
    }

    /* Counts the number of relations */
    for (j = 0; j < r->num_music; j++) {
        if (r->relations[i][j] == TRUE) {
            counter++;
        }
    }

    return counter;
}

long *radio_getRelationsFromId(const Radio *r, long id) {
    long *rel = NULL;
    int counter;
    int i, j;
    int k = 0;

    /* Control error */
    if (!r) {
        return NULL;
    }

    i = radio_findId(r, id);

    if (i == -1) {
        return NULL;
    }

    /* Gets the number of relations */
    counter = radio_getNumberOfRelationsFromId(r, id);
    if (counter <= 0) {
        return NULL;
    }

    /* Allocates memory for the relations */
    if (!(rel = (long *) calloc (counter, sizeof(long)))) {
        return NULL;
    }

    /* Checks if the relation is valid and stores it in the array if they are valid */
    for (j = 0; j < r->num_music; j++) {
        if (r->relations[i][j] == TRUE) {
            rel[k++] = music_getId(r->songs[j]);
        }
    }

    return rel;
}

int radio_print(FILE *pf, const Radio *r) {
    int counter = 0;
    int i, j;

    /* Control error */
    if (!pf || !r) {
        return -1;
    }

    for (i = 0; i < r->num_music; i++) {
        /* Prints the music without format (line) */
        counter += music_plain_print(pf, r->songs[i]);

        /* Prints the relations */
        for (j = 0; j < r->num_music; j++) {
            if (r->relations[i][j] == TRUE) {
                fprintf(pf, ": ");
                counter += music_plain_print(pf, r->songs[j]);
            }
        }

        counter += fprintf(pf, "\n");
    }

    return counter;
}

Status radio_readFromFile(FILE *fin, Radio *r, Stack *stack) {
    char scan_file[MAX_FILE];
    char buffer[STR_LENGTH * 4];
    int i;

    /* Control error */
    if (!fin || !r || !stack) {
        return ERROR;
    }

    /* Reads the number of songs that the file has */
    if((fgets(scan_file, sizeof(scan_file), fin)) == NULL){
        return ERROR;
    }

    /* Reads the songs one by one */
    for (i = 0; i < atoi(scan_file); i++) {
        if (fgets(buffer, sizeof(buffer), fin) == NULL) break;

        if (radio_newMusic(r, buffer) == ERROR) {
            return ERROR;
        }

        if (stack_push(stack, r->songs[r->num_music - 1]) == ERROR) {
            return ERROR;
        }
    }

    return OK;
}

Status radio_depthSearch(Radio *r, long from_id, long to_id) {
    Music *mi = NULL;
    Music *mf = NULL;
    Music *current = NULL;
    Music *neighbor = NULL;
    Stack *s = NULL;
    Bool found = FALSE;
    int i, j, current_index;

    if (!r || from_id < 0 || to_id < 0) {
        return ERROR;
    }

    i = radio_findId(r, from_id);
    j = radio_findId(r, to_id);

    if (i == -1 || j == -1) {
        return ERROR;
    }

    mi = r->songs[i];
    mf = r->songs[j];

    for (i = 0; i < r->num_music; i++) {
        music_setState(r->songs[i], NOT_LISTENED);
    }

    if (!(s = stack_init())) {
        return ERROR;
    }

    music_setState(mi, LISTENED);
    if (stack_push(s, mi) == ERROR) {
        stack_free(s);
        return ERROR;
    }

    while ((stack_isEmpty(s) == FALSE) && (found == FALSE)) {
        if (!(current = (Music *)stack_pop(s))) {
            break;
        }

        music_plain_print(stdout, current);
        fprintf(stdout, "\n");

        if (music_getId(current) == music_getId(mf)) {
            found = TRUE;
        } else {
            current_index = music_getIndex(current);
            for (j = 0; j < r->num_music; j++) {
                if (r->relations[current_index][j] == TRUE) {
                    neighbor = r->songs[j];
                    if (music_getState(neighbor) == NOT_LISTENED) {
                        music_setState(neighbor, LISTENED);
                        if (stack_push(s, neighbor) == ERROR) {
                            stack_free(s);
                            return ERROR;
                        }
                    }
                } 
            }
        }
    }

    stack_free(s);

    return OK;
}

Status radio_readRelationsFromFile(FILE *fin, Radio *r) {
    long orig, dest;

    /* Control error */
    if (!fin || !r) {
        return ERROR;
    }

    /* Reads pairs until the file has no relation count */
    while (fscanf(fin, "%ld %ld\n", &orig, &dest) == 2) {
        if (radio_newRelation(r, orig, dest) == ERROR) {
            return ERROR;
        }
    }

    return OK;
}