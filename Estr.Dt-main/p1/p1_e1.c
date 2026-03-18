/**
 * @file  p1_ej1
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
#include <string.h>
#include "music.h"

int main () {
    Music *m1 = NULL;
    Music *m2 = NULL;
    Music *m3 = NULL;
    int cmp;

   if (!(m1 = music_init()) || !(m2 = music_init())) {
    fprintf(stdout, "Error creating music\n");
    return 1;
   }

    /* First song data */
    music_setId(m1, 10);
    music_setTitle(m1, "Blinding Lights");
    music_setArtist(m1, "The Weekend");
    music_setDuration(m1, 200);

    /* Second song data */
    music_setId(m2, 20);
    music_setTitle(m2, "Bohemian Rhapsody");
    music_setArtist(m2, "Queen");
    music_setDuration(m2, 355);

    /* Prints both songs */
    music_formatted_print(stdout, m1);
    music_formatted_print(stdout, m2);
    fprintf(stdout, "\n");

    /* Compares the first and the second song */
    cmp = music_cmp(m1, m2);

    if (cmp != 0) {
        fprintf(stdout, "Equals? No\n");
    } else {
        fprintf(stdout, "Equals? Yes\n");
    }
        
    /* Prints second song title */
    printf("Music 2 title: %s\n", music_getTitle(m2));

    /* Copies the first song in a third one */
    if (!(m3 = music_copy(m1))) {
        fprintf(stdout, "Error copying music\n");
        music_free(m1);
        music_free(m2);
        return 1;
    }

    /* Prints the id of the third song */
    fprintf(stdout, "Music 3 id: %ld\n", music_getId(m3));

    /* Plays the first and the third song */
    music_formatted_print(stdout, m1);
    music_formatted_print(stdout, m3);
    printf("\n");

    /* Compares the first and the third song */
    cmp = music_cmp(m1, m3);

    /* Determines if the songs are equal or not */
    if (cmp != 0) {
        fprintf(stdout, "Equals? No\n");
    } else {
        fprintf(stdout, "Equals? Yes\n");
    }

    /* Clears memory */
    music_free(m1);
    music_free(m2);
    music_free(m3);

    return 0;
}