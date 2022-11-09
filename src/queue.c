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

#include "queue.h"

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
    queue -> tail -> next = temp;
    queue -> tail = temp;
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
    return 0;
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
