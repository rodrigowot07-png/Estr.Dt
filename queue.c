#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define MAX_QUEUE 100

struct _Queue {
    void *data[MAX_QUEUE];
    void **front;
    void **rear;
};

/* Private functions */

Bool _queue_is_full(const Queue *pq) {
    if (pq == NULL) {
        return TRUE;
    }

    if ((pq->rear + 1 - pq->front) % MAX_QUEUE == 0) {
        return TRUE;
    }

    return FALSE;
}

/* Public functions */

Queue *queue_new() {
    Queue *pq = NULL;
    int i;

    pq = (Queue *)malloc(sizeof(Queue));
    if (pq == NULL) {
        return NULL;
    }

    for (i = 0; i < MAX_QUEUE; i++) {
        pq->data[i] = NULL;
    }

    pq->front = &(pq->data[0]);
    pq->rear = &(pq->data[0]);

    return pq;
}

void queue_free(Queue *pq) { free((void *)pq); }

Bool queue_is_empty(const Queue *pq) {
    if (pq == NULL) {
        return TRUE;
    }

    if (pq->front == pq->rear) {
        return TRUE;
    }

    return FALSE;
}

Status queue_push(Queue *pq, void *e) {
    if ((pq == NULL) || (e == NULL) || (_queue_is_full(pq) == TRUE)) {
        return ERROR;
    }

    *(pq->rear) = (void *)e;
    pq->rear = pq->data + (pq->rear + 1 - pq->data) % MAX_QUEUE;

    return OK;
}

void *queue_pop(Queue *pq) {
    void *e = NULL;

    if ((pq == NULL) || (queue_is_empty(pq) == TRUE)) {
        return NULL;
    }

    e = *(pq->front);
    *(pq->front) = NULL;

    pq->front = pq->data + (pq->front + 1 - pq->data) % MAX_QUEUE;

    return e;
}

void *queue_get_front(const Queue *pq) {
    if ((pq == NULL) || (queue_is_empty(pq) == TRUE)) {
        return NULL;
    }

    return *(pq->front);
}

void *queue_get_back(const Queue *pq) {
    void **last_elem;

    if ((pq == NULL) || (queue_is_empty(pq) == TRUE)) {
        return NULL;
    }

    if (pq->rear == pq->data) {
        last_elem = ((Queue *)pq)->data + MAX_QUEUE - 1;
    } else {
        last_elem = pq->rear - 1;
    }

    return *last_elem;
}

size_t queue_size(const Queue* pq) {
    int i, counter;

    if(pq == NULL) {
        return -1;
    }

    if(pq->rear >= pq->front) {
        return pq->rear -pq->front;
    } else {
        return MAX_QUEUE - (pq->front - pq->rear);
    }
}

int queue_print(FILE *fp, const Queue *pq, p_queue_ele_print f) {
  int i = pq->front, n=0;

  if (!pq || !fp) {
    return -1;
  }

  fprintf(fp, "SIZE: %lu\n", queue_size(pq));

  while (i != pq->rear) {
    n += f(fp, pq->data[i]);
    fprintf(fp, "\n");

    i = (i+1) % MAX_QUEUE;
  }

  return n;
}