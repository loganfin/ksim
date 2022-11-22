#pragma once

#include <string>

#include "node.hpp"
#include "process.hpp"

class Queue_t {
    public:
        Queue_t();
        Queue_t(std::string);
        //Queue_t(Process_t *);
        ~Queue_t();
        //int set_name(std::string);
        int create_process(std::string);
        Process_t *detach_head();
        int enqueue(Process_t *);
        int kill_head();
        std::string top();
        void print();
    private:
        std::string name;
        Process_t *head;
        Process_t *tail;
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
