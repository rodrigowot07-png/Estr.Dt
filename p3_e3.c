#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "music.h"
#include "list.h"

#define MAX_LINE 500

int main(int argc, char *argv[]) {
    FILE *fin = NULL;
    List *list = NULL;
    Music *m = NULL;
    void *elem = NULL;
    char buffer[MAX_LINE];
    int num_songs, i, size, half, remaining;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radio_file>\n", argv[0]);
        return 1;
    }

    fin = fopen(argv[1], "r");
    if (!fin) {
        fprintf(stderr, "Error: cannot open file '%s'\n", argv[1]);
        return 1;
    }

    list = list_new();
    if (!list) {
        fclose(fin);
        return 1;
    }

    if (fgets(buffer, sizeof(buffer), fin) == NULL) {
        list_free(list);
        fclose(fin);
        return 1;
    }

    num_songs = atoi(buffer);

    for (i = 1; i <= num_songs; i++) {
        if (fgets(buffer, sizeof(buffer), fin) == NULL) {
            break;
        }

        m = music_initFromString(buffer);
        if (!m) {
            list_free(list);
            fclose(fin);
            return 1;
        }

        if (i % 2 == 1) {
            if (list_pushBack(list, m) == ERROR) {
                music_free(m);
                list_free(list);
                fclose(fin);
                return 1;
            }
        } else {
            if (list_pushFront(list, m) == ERROR) {
                music_free(m);
                list_free(list);
                fclose(fin);
                return 1;
            }
        }
    }

    fclose(fin);

    list_print(stdout, list, music_plain_print);

    size = list_size(list);
    half = size / 2;

    printf("\nFinished inserting. Now we extract from the beginning:\n");
    for (i = 0; i < half; i++) {
        elem = list_popFront(list);
        if (!elem) {
            break;
        }
        music_plain_print(stdout, elem);
        if (i < half - 1) {
            printf(" ");
        }
        music_free(elem);
    }
    printf("\n");

    remaining = list_size(list);

    printf("\nNow we extract from the end:\n");

    for (i = 0; i < remaining; i++) {
        elem = list_popBack(list);
        if (!elem) {
            break;
        }

        music_plain_print(stdout, elem);
        if (i < remaining - 1) {
            printf(" ");
        }
        
        music_free(elem);
    }
    printf("\n");

    list_free(list);

    return 0;
}