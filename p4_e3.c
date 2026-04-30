/**
 * @file  p4_e3.c
 * @brief Ejercicio 4: Filtrar canciones por duración minima
 *
*/
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "music.h"
#include "radio.h"
#include "bstree.h"

int main (int argc, int *argv[]) {


    if (argc != 3) {
        fprintf(stderr, "Use: %s <music_file> <duration_min>", argv[0]);
        return 1;
    }
}