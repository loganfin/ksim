#pragma once

typedef struct Node_t {
    //char *data;
    int data;
    struct Node_t* next;
} Node_t;

typedef struct Queue_t {
    struct Node_t* head;
    struct Node_t* tail;
} Queue_t;

Node_t *node_create(int);
Queue_t *queue_create();
int enqueue(Queue_t *, int);
int dequeue(Queue_t *);
int queue_print(Queue_t *);

/*
int front(char[]);
int rear(char
int queue_clean(Queue_t *);
*/
