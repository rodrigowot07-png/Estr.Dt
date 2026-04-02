#include <stdio.h>
#include <stdlib.h>
 
#include "queue.h"
#include "list.h"
 
struct _Queue {
    List *pl;
};
 
Queue *queue_new() {
    Queue *pq = (Queue *)malloc(sizeof(Queue));
    if (!pq) {
        return NULL;
    }
 
    pq->pl = list_new();
    if (!pq->pl) {
        free(pq);
        return NULL;
    }
 
    return pq;
}
 
void queue_free(Queue *pq) {
    if (!pq) {
        return;
    }
 
    list_free(pq->pl);
    free(pq);
}
 
Bool queue_isEmpty(const Queue *pq) {
    if (!pq) {
        return TRUE;
    }
 
    return list_isEmpty(pq->pl);
}
 
Status queue_push(Queue *pq, void *e) {
    if (!pq || !e) {
        return ERROR;
    }
 
    return list_pushBack(pq->pl, e);
}
 
void *queue_pop(Queue *pq) {
    if (!pq || queue_isEmpty(pq)) {
        return NULL;
    }
 
    return list_popFront(pq->pl);
}
 
void *queue_getFront(const Queue *pq) {
    if (!pq || queue_isEmpty(pq)) {
        return NULL;
    }
 
    return list_getFront(pq->pl);
}
 
void *queue_getBack(const Queue *pq) {
    if (!pq || queue_isEmpty(pq)) {
        return NULL;
    }
 
    return list_getBack(pq->pl);
}
 
size_t queue_size(const Queue *pq) {
    if (!pq) {
        return -1;
    }
 
    return list_size(pq->pl);
}
 
int queue_print(FILE *fp, const Queue *pq, p_queue_ele_print f) {
    if (!fp || !pq || !f) {
        return -1;
    }
 
    return list_print(fp, pq->pl, f);
}