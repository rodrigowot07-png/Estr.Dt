#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "radio.h"
#include "types.h"

/* START Private methods */
int mainCleanUp (int ret_value, Radio *r, FILE *pf) {
  radio_free(r);   
  fclose(pf);
  exit(ret_value);
}

void loadBalancedTree_rec(Music **sorted_data, BSTree *t, int first, int last) {
  int middle = (first + last) / 2;
  Music *m;

  if (first <= last) {
    m = *(&(sorted_data[0]) + middle);
    if (tree_insert(t, m) == ERROR) {
      fprintf(stdout, "Music ");
      music_plain_print(stdout, m);
      fprintf(stdout, " not inserted!\n");
    }

    loadBalancedTree_rec(sorted_data, t, first, middle - 1);
    loadBalancedTree_rec(sorted_data, t, middle + 1, last);
  }
}

BSTree *loadBalancedTree(Music **data, int n) {
  BSTree *t;

  if (!data || (n <= 0)) {
    return NULL;
  }

  if (!(t = tree_init(music_plain_print, music_cmp))) { 
    return NULL;
  }

  loadBalancedTree_rec(data, t, 0, n - 1);

  return t;
}

BSTree *loadUnbalancedTree(Music **data, int n) {
  BSTree *t;
  Music *m;
  int i;

  if (!data || (n <= 0)) {
    return NULL;
  }

  if (!(t = tree_init(music_plain_print, music_cmp))) {
    return NULL;
  }

  for (i = 0; i < n; i++) {
    m = data[i];
    if (tree_insert(t, m) == ERROR) {
      fprintf(stdout, "Music ");
      music_plain_print(stdout, m);
      fprintf(stdout, " not inserted!\n");
    }
  }

  return t;
}

int qsort_fun(const void *e1, const void *e2){
  Music **pm1, **pm2;

  pm1 = (Music **) e1;
  pm2 = (Music **) e2;

  return music_cmp(*pm1, *pm2);
}
/* END Private methods */


int main(int argc, char const *argv[]) {
	FILE *f_in = NULL, *f_out = NULL;
	BSTree *t = NULL;
	Music **songs=NULL, *m;
	const char *mode;
	int n, index=0;
	long	music_id;
	time_t time;
	Radio *r = NULL;

	if (argc != 4) {
		printf("Usage: %s music_file music_id mode[normal|sorted]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	mode = argv[3];
	if (strcmp(mode, "normal") && strcmp(mode, "sorted")) {
		printf("Incorrect mode: %s\n", mode);
		exit(EXIT_FAILURE);
	}

    f_in = fopen(argv[1], "r");
    if (!f_in) {
      return (EXIT_FAILURE);
    }
	f_out = stdout;

    r = radio_init();
    if (!r) mainCleanUp (EXIT_FAILURE, r, f_in);
    
    /* lee el fichero */
    if  (radio_readFromFile(f_in, r) == ERROR) {
      fprintf(stdout, "Not file or File format incorrect\n");
      mainCleanUp (EXIT_FAILURE, r, f_in);
    }
	
	music_id = atoi(argv[2]);
	/* REPLACE BY YOUR OWN IMPLEMENTED FUNCTIONS */
	songs = radio_getSongs(r);
	n = radio_getNumberOfMusic(r);
	
	index = _radio_findmusicById(r, music_id);
	m = songs[index];
	if (m == NULL) {
		printf("Error when initialising music with id: %ld\n", music_id);
		mainCleanUp (EXIT_FAILURE, r, f_in);
	}
	/* END REPLACE */

	if (!strcmp(mode, "normal")) {
		fprintf(f_out, "Mode: normal\n");
		time = clock();
		t = loadUnbalancedTree(songs, n);
		time = clock() - time;
	}
	else {
		qsort(songs, n, sizeof(Music *), qsort_fun);
		fprintf(f_out, "Mode: sorted\n");
		time = clock();
		t = loadBalancedTree(songs, n);
		time = clock() - time;
	}

  if (!t) {
    mainCleanUp (EXIT_FAILURE, r, f_in);
  }

  fprintf(f_out, "Tree building time: %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
  fprintf(f_out, "Tree size: %ld\nTree depth: %d\n", tree_size(t), tree_depth(t));

  fprintf(f_out, "Min element in tree: ");
  time = clock();
  music_plain_print(f_out, tree_find_min(t));
  time = clock() - time;
  fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);

  fprintf(f_out, "Max element in tree: ");
  time = clock();
  music_plain_print(f_out, tree_find_max(t));
  time = clock() - time;
  fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);

  time = clock();
  if (tree_contains(t, m) == TRUE) {
    fprintf(f_out, "Element found");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);

/*EXERCISE 2 - TREE_REMOVE
    fprintf(f_out, "Removing element in tree: ");
    time = clock();
    fprintf(f_out, "%s", tree_remove(t, m) == OK ? "OK" : "ERR");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
    fprintf(f_out, "Tree size: %ld\nTree depth: %d\n", tree_size(t), tree_depth(t));
*/
  } else {
    fprintf(f_out, "Element NOT found");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
  }
  
  tree_destroy(t);
  mainCleanUp (EXIT_SUCCESS, r, f_in);

  return 0;
}
/*
 * P1: ¿Por qué los tiempos y la profundidad varían según el modo normal o sorted?
 *
 * En modo "normal" las canciones se insertan en orden aleatorio (tal como
 * aparecen en el fichero). Esto genera un árbol aproximadamente balanceado,
 * donde la profundidad crece como O(log n). Con 10 canciones la profundidad
 * es 6; con 100 es 16; con 1000 es 20. Las operaciones find_min, find_max y
 * contains recorren caminos cortos desde la raíz.
 *
 * En modo "sorted" el array se ordena por id con qsort antes de insertar,
 * pero en vez de insertarlo secuencialmente (lo que daría un árbol lineal),
 * la función loadBalancedTree inserta siempre el elemento central del rango
 * actual, lo que construye un árbol perfectamente balanceado con profundidad
 * O(log n) garantizada. Con 10 canciones la profundidad es 4; con 100 es 7;
 * con 1000 es 10. Esto explica por qué sorted es mas eficiente que normal:
 * la estrategia de inserción por la mitad produce el árbol óptimo.
 *
 * Si en modo sorted se insertasen en orden creciente, el árbol
 * degeneraría en una lista enlazada con profundidad O(n), haciendo las
 * búsquedas extremadamente lentas. Esta es la principal debilidad de un BST
 * no balanceado. 
 */