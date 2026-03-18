/**
 * @file  p1_ej3
 * @author Nicolas Encinas y Rodrigo Martin
 * @date February 2026
 * @mersion 1.0
 * @brief Reeds the information of the file and prints the radio
 * @details 
 * 
 * @see
 */

#include <stdio.h>
#include <stdlib.h>
#include "radio.h"
#include "music.h"
#include "types.h"

int main (int argc, char *argv[]){
    FILE *fin = NULL;
    Radio *rad = NULL;
    Status stat;

    /* Initializes the radio, checking if there are any errors */
    if (!(rad = radio_init())) {
        fprintf(stderr, "Error initializing the radio\n");
        return 1;
    }

    /* Open the file */
    if(!(fin = fopen(argv[1], "r"))){
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }

    /* Read the file */
    stat = radio_readFromFile(fin, rad);
    if(stat == ERROR){
        fprintf(stderr, "Error reading the file\n");
        return 1;
    }

    /* Prints the radio */
    fprintf(stdout, "All radio reccomendations:\n");
    radio_print(stdout, rad);

    /* Close the file */
    fclose(fin);

    /* Frees the memory of the radio and the music*/
    radio_free(rad);

    return 0;
}