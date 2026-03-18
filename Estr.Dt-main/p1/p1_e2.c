/**
 * @file  p1_ej2
 * @author Nicolas Encinas y Rodrigo Martin
 * @date February 2026
 * @mersion 1.0
 * @brief Manage the relations of the radio
 *
 * @details 
 * 
 * @see
 */

#include <stdio.h>
#include <stdlib.h>
#include "radio.h"
#include "music.h"
#include "types.h"

int main() {
    Radio *rad = NULL;
    Status stat;

    /* Initializes the radio, checking if there are any errors */
    if (!(rad = radio_init())) {
        fprintf(stderr, "Error initializing the radio\n");
        return 1;
    }

    /* Initializes the new music and prints if it goes well */
    stat = radio_newMusic(rad, "id:\"111\" title:\"Paint It, Black\" artist:\"The Rolling Stones\" duration:\"202\" state:\"0\"");
    fprintf(stdout, "Inserting: Paint It, Black... result...: ");
    if(stat == OK){
        fprintf(stdout, "1\n");
    }
    else{
        fprintf(stdout, "0\n");
    }

    stat = radio_newMusic(rad, "id:\"222\" title:\"Every Breath You Take\" artist:\"The Police\" duration:\"253\" state:\"0\"");
    fprintf(stdout, "Inserting: Every Breath You Take... result...: ");
    if(stat == OK){
        fprintf(stdout, "1\n\n");
    }
    else{
        fprintf(stdout, "0\n\n");
    }

    /* Creates a new relation between two ids */
    stat = radio_newRelation(rad, 222, 111);
    fprintf(stdout, "Inserting radio recommendation: 222 --> 111\n\n");

    /* Prints the relations */
    fprintf(stdout, "111 --> 222? ");
    if(radio_relationExists(rad, 111, 222) == TRUE){
        fprintf(stdout, "Yes\n");
    }
    else{
        fprintf(stdout, "No\n");
    }

    fprintf(stdout, "222 --> 111? ");
    if(radio_relationExists(rad, 222, 111) == TRUE){
        fprintf(stdout, "Yes\n");
    }
    else{
        fprintf(stdout, "No\n");
    }

    /* Prints the connections */
    fprintf(stdout, "Number of connections from 111: %d\n", radio_getNumberOfRelationsFromId(rad, 111));
    fprintf(stdout, "Number of connections from 222: %d\n", radio_getNumberOfRelationsFromId(rad, 222));

    /* Prints the radio */
    fprintf(stdout, "All radio reccomendations:\n");
    radio_print(stdout, rad);

    /* Frees the memory of the radio and the music */
    radio_free(rad);

    return 0;
}



