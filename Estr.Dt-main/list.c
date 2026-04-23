/**
 * @file list.c
 * @brief Implementation of the List ADT as a singly linked list
 *        with front and rear access.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

struct _Node {
    void *info;
    struct _Node *next;
};

typedef struct _Node Node;

struct _List {
    Node *first;
    Node *last;
    int size;
};

static Node *_node_new(const void *e) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) {
        return NULL;
    }

    n->info = (void *)e;
    n->next = NULL;

    return n;
}

List *list_new() {
    List *pl = NULL;

    pl = (List *)calloc(1, sizeof(List));
    if (!pl) {
        return NULL;
    }

    pl->first = NULL;
    pl->last = NULL;
    pl->size = 0;

    return pl;
}

Bool list_isEmpty(const List *pl) {
    if (!pl || pl->size == 0) {
        return TRUE;
    }
    return FALSE;
}

Status list_pushFront(List *pl, const void *e) {
    Node *n = NULL;

    if (!pl || !e) {
        return ERROR;
    }

    n = _node_new(e);
    if (!n) {
        return ERROR;
    }

    n->next = pl->first;
    pl->first = n;

    if (pl->last == NULL) {
        pl->last = n;
    }

    pl->size++;

    return OK;
}

Status list_pushBack(List *pl, const void *e) {
    Node *n = NULL;

    if (!pl || !e) {
        return ERROR;
    }

    n = _node_new(e);
    if (!n) {
        return ERROR;
    }

    if (pl->last == NULL) {
        pl->first = n;
        pl->last = n;
    } else {
        pl->last->next = n;
        pl->last = n;
    }

    pl->size++;
    return OK;
}

void *list_popFront(List *pl) {
    Node *n = NULL;
    void *e;

    if (!pl || list_isEmpty(pl)) {
        return NULL;
    }

    n = pl->first;
    e = n->info;
    pl->first = n->next;

    if (pl->first == NULL) {
        pl->last = NULL;
    }

    free(n);
    pl->size--;

    return e;
}

void *list_popBack(List *pl) {
    Node *n = NULL, *prev = NULL;
    void *e;

    if (!pl || list_isEmpty(pl)) {
        return NULL;
    }

    if (pl->first == pl->last) {
        n = pl->first;
        e = n->info;
        pl->first = NULL;
        pl->last = NULL;
        free(n);
        pl->size--;
        return e;
    }

    prev = pl->first;
    while (prev->next != pl->last) {
        prev = prev->next;
    }

    n = pl->last;
    e = n->info;
    prev->next = NULL;
    pl->last = prev;

    free(n);
    pl->size--;

    return e;
}

void *list_getFront(List *pl) {
    if (!pl || list_isEmpty(pl)) {
        return NULL;
    }

    return pl->first->info;
}

void *list_getBack(List *pl) {
    if (!pl || list_isEmpty(pl)) {
        return NULL;
    }

    return pl->last->info;
}

void list_free(List *pl) {
    Node *curr = NULL, *next = NULL;

    if (!pl) {
        return;
    }

    curr = pl->first;
    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    free(pl);
}

int list_size(const List *pl) {
    if (!pl) {
        return -1;
    }

    return pl->size;
}

int list_print(FILE *fp, const List *pl, p_list_ele_print f) {
    Node *curr = NULL;
    int total = 0, ret;

    if (!fp || !pl || !f) {
        return -1;
    }

    curr = pl->first;
    while (curr) {
        ret = f(fp, curr->info);
        fprintf(fp, "\n");
        if (ret < 0) {
            return ret;
        }

        total += ret;
        curr = curr->next;
    }

    return total;
}