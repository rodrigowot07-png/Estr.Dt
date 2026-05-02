/**
 * @file  p4_e2.c
 * @brief Ejercicio 3: Filtrar canciones por rango de id usando tree_rangeSearch.
 *
*/
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "music.h"
#include "radio.h"
#include "list.h"
#include "bstree.h"

int music_cmp_id(const void *m1, const void *m2) {
    const Music *a = (const Music *)m1;
    const Music *b = (const Music *)m2;

    if (!a && !b) return  0;
    if (!a) return -1;
    if (!b) return  1;

    if (music_getId(a) < music_getId(b)) return -1;
    if (music_getId(a) > music_getId(b)) return  1;

    return 0;
}

int main(int argc, char *argv[]) {
    FILE *fin = NULL;
    Radio *radio = NULL;
    BSTree *tree = NULL;
    List *result = NULL;
    Music *min_key = NULL;
    Music *max_key = NULL;
    Music **songs  = NULL;
    long id_min, id_max;
    int i, n;

    if (argc != 4) {
        fprintf(stderr, "Use: %s <music_file> <id_min> <id_max>\n", argv[0]);
        return 1;
    }

    id_min = atol(argv[2]);
    id_max = atol(argv[3]);

    if (id_min < 0 || id_max < 0 || id_min > id_max) {
        fprintf(stderr, "Error: ids invalidos. Se requiere 0 <= id_min <= id_max.\n");
        return 1;
    }

    fin = fopen(argv[1], "r");
    if (!fin) {
        fprintf(stderr, "Error: no se pudo abrir el fichero '%s'.\n", argv[1]);
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

    tree = tree_init(music_plain_print, music_cmp_id);
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

    min_key = music_init();
    max_key = music_init();
    if (!min_key || !max_key) {
        fprintf(stderr, "Error: no se pudieron crear las claves de busqueda.\n");
        music_free(min_key);
        music_free(max_key);
        tree_destroy(tree);
        radio_free(radio);
        return 1;
    }

    music_setId(min_key, id_min);
    music_setId(max_key, id_max);

    result = tree_rangeSearch(tree, min_key, max_key);

    fprintf(stderr, "Lista de canciones desde id %ld hasta id %ld\n", id_min, id_max);

    if (!result || list_isEmpty(result)) {
        fprintf(stderr, "(No hay canciones en ese rango)\n");
    } else {
        list_print(stdout, result, music_plain_print);
    }

    list_free(result);
    music_free(min_key);
    music_free(max_key);
    tree_destroy(tree);
    radio_free(radio);

    return 0;
}

/*
 * P2:
 *
 * La lista resultante de tree_rangeSearch esta ordenada de menor a mayor id, esto se debe a que tree_rangeSearchRec realiza un recorrido de tipo in-order
 * (izquierda -> nodo -> derecha):
 *   - Solo va al subarbol izquierdo si el nodo actual es estrictamente mayor que el minimo.
 *   - Solo va al subarbol derecho si el nodo actual es estrictamente menor que el maximo.
 *   - Anade el nodo a la lista si su id esta dentro del rango [id_min, id_max].
 *
 * Dado que el BST se construye con music_cmp_id, el in-order produce
 * exactamente los elementos en orden creciente de id. Los elementos se insertan en la
 * lista mediante list_pushBack, por lo que la lista resultante queda ordenada
 * de menor a mayor id: es una consecuencia directa de la propiedad de orden del BST
 * combinada con el recorrido in-order de tree_rangeSearchRec.
 */