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

int music_cmp_duration(const void *m1, const void *min_duration) {
    const Music *a = (const Music *)m1;
    const int *dm = (const int *)min_duration;

    if(!a || !dm) return 0; 

    if(music_getDuration(a) > *dm) return 1;
    if(music_getDuration(a) < *dm) return -1;

    return 0;
}

int main (int argc, char *argv[]) {
    FILE *fin = NULL;
    Radio *radio = NULL;
    BSTree *tree = NULL;
    Music **songs  = NULL;
    int i, n, min_duration, result;

    if (argc != 3) {
        fprintf(stderr, "Use: %s <music_file> <duration_min>\n", argv[0]);
        return 1;
    }

    fin = fopen(argv[1], "r");
    if (!fin) {
        fprintf(stderr, "Error: no se pudo abrir el fichero '%s'.\n", argv[1]);
        return 1;
    }

    min_duration = atoi(argv[2]);
    if (min_duration < 0) {
        fprintf(stderr, "Error: duración invalida. Se requiere una duración > 0\n");
        return 1;
    }

    radio = radio_init();
    if (!radio) {
        fprintf(stderr, "Error: no se pudo inicializar la radio.\n");
        fclose(fin);
        return 1;
    }

    if (radio_readFromFile(fin, radio) == ERROR) {
        fprintf(stderr, "Error: fallo al leer canciones del fichero.\n");
        radio_free(radio);
        fclose(fin);
        return 1;
    }
    fclose(fin);

    tree = tree_init(music_plain_print, music_cmp_duration);
    if (!tree) {
        fprintf(stderr, "Error: no se pudo inicializar el arbol.\n");
        radio_free(radio);
        return 1;
    }

    n = radio_getNumberOfMusic(radio);
    songs = radio_getSongs(radio);

    for (i = 0; i < n; i++) {
        if (tree_insert(tree, songs[i]) == ERROR) {
            fprintf(stderr, "Error: fallo al insertar cancion en el arbol.\n");
            tree_destroy(tree);
            radio_free(radio);
            return 1;
        }
    }

    result = tree_countLongSongs(tree, min_duration);

    fprintf(stderr, "Número de canciones con duración mayor a %d segundos: %d\n", min_duration, result);

    tree_destroy(tree);
    radio_free(radio);

    return 0;
}