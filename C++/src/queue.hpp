#pragma once

#include "node.hpp"
#include "process.hpp"

class Queue_t {
    public:
        Queue_t();
        Queue_t(Process_t *);
        ~Queue_t();
        int enqueue(Process_t *);
        Process_t *dequeue();
        Process_t *top();
        void print();
    private:
        Node_t *head;
        Node_t *tail;
};

/*
typedef struct Node_t {
    //char *data;
    // this data ideally be a `process` pointer
    // Process_t *process;
    int data;
    struct Node_t* next;
} Node_t;
*/

/*
typedef struct Queue_t {
    struct Node_t* head;
    struct Node_t* tail;
} Queue_t;
*/

Node_t *node_create(int);
Queue_t *queue_create();

// int enqueue(Queue_t *, Process_t *)
int enqueue(Queue_t *, int);

// Process_t *dequeue(Queue_t *);
int dequeue(Queue_t *);
int queue_print(Queue_t *);
int queue_clean(Queue_t *);

/*
Process_t front(Queue_t *);
Process_t rear(Queue_t *);
*/
