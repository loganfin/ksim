/*
 sample use:
  int error = 0
  Queue_t ready;
  error = queue_init(&ready);
  if (error != 0) {
  }
  */

#include <stdlib.h>
#include <stdio.h>

#include "queue.hpp"
//#include "process.h"

Node_t *node_create(int str)
{
    Node_t *node = malloc(sizeof(*node));
    if (node == NULL) {
        return node;
    }
    node -> data = str;
    node -> next = NULL;
    return node;
}

Queue_t *queue_create()
{
    // check if queue is already initialized
    Queue_t *queue = malloc(sizeof(*queue));
    // is this if necessary?
    if (queue == NULL) {
        return queue;
    }
    queue -> head = NULL;
    queue -> tail = NULL;
    return queue;
}

int enqueue(Queue_t *queue, int data)
{
    // set tail -> next = a new node
    // set tail == new node
    // if the queue is empty, set the head equal to the new node
    Node_t *temp = node_create(data);
    if (temp == NULL) {
        return 1;
    }
    if (queue -> head == NULL) {
        //queue -> head -> next = temp;
        queue -> head = temp;
        queue -> tail = temp;
    }
    else {
        queue -> tail -> next = temp;
        queue -> tail = temp;
    }
    return 0;

    /*
    Node_t *temp = node_create(data);
    if (queue -> head == NULL) {
        queue -> head = temp;
        queue -> tail = temp;
    }
    queue -> tail -> next = temp;
    queue -> tail = temp;
    return 0;
    */
}

int dequeue(Queue_t *queue)
{
    /* example use:
     * enqueue(blocked, dequeue(ready));
     */
    // should this return the value of the popped data?
    // set the new head equal to head -> next
    // remove / free the head

    // Process_t temp_data = NULL;
    int temp_data = 0;
    Node_t *temp = NULL;
    if (queue -> head == NULL) {
        return temp_data;
    }

    temp_data = queue -> head -> data;
    temp = queue -> head;
    queue -> head = queue -> head -> next;

    if (queue -> head == NULL) {
        queue -> tail = NULL;
    }
    free(temp);
    return temp_data;
}

int queue_print(Queue_t *queue)
{
    Node_t *prev = queue -> head;
    while (queue -> head != NULL) {
        printf("%d\n", queue -> head -> data);
        prev = queue -> head;
        queue -> head = queue -> head -> next;
    }
    return 0;
}

int queue_clean(Queue_t *queue)
{
    // while head is not NULL, dequeue
    while (queue -> head != NULL) {
        dequeue(queue);
    }
    return 0;
}

