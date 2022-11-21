/*
 sample use:
  int error = 0
  Queue_t ready;
  error = queue_init(&ready);
  if (error != 0) {
  }
  */

#include <stdlib.h>
#include <iostream>

#include "node.hpp"
#include "process.hpp"
#include "queue.hpp"
//#include "process.h"

// int Node_t::*node_create(int str)
// {
//     Node_t *node = malloc(sizeof(*node));
//     if (node == NULL) {
//         return node;
//     }
//     node -> data = str;
//     node -> next = NULL;
//     return node;
// }
// 
// Queue_t *queue_create()
// {
//     // check if queue is already initialized
//     Queue_t *queue = malloc(sizeof(*queue));
//     // is this if necessary?
//     if (queue == NULL) {
//         return queue;
//     }
//     queue -> head = NULL;
//     queue -> tail = NULL;
//     return queue;
// }
// 
// int enqueue(Queue_t *queue, int data)
// {
//     // set tail -> next = a new node
//     // set tail == new node
//     // if the queue is empty, set the head equal to the new node
//     Node_t *temp = node_create(data);
//     if (temp == NULL) {
//         return 1;
//     }
//     if (queue -> head == NULL) {
//         //queue -> head -> next = temp;
//         queue -> head = temp;
//         queue -> tail = temp;
//     }
//     else {
//         queue -> tail -> next = temp;
//         queue -> tail = temp;
//     }
//     return 0;
// 
//     /*
//     Node_t *temp = node_create(data);
//     if (queue -> head == NULL) {
//         queue -> head = temp;
//         queue -> tail = temp;
//     }
//     queue -> tail -> next = temp;
//     queue -> tail = temp;
//     return 0;
//     */
// }
// 
// int dequeue(Queue_t *queue)
// {
//     /* example use:
//      * enqueue(blocked, dequeue(ready));
//      */
//     // should this return the value of the popped data?
//     // set the new head equal to head -> next
//     // remove / free the head
// 
//     // Process_t temp_data = NULL;
//     int temp_data = 0;
//     Node_t *temp = NULL;
//     if (queue -> head == NULL) {
//         return temp_data;
//     }
// 
//     temp_data = queue -> head -> data;
//     temp = queue -> head;
//     queue -> head = queue -> head -> next;
// 
//     if (queue -> head == NULL) {
//         queue -> tail = NULL;
//     }
//     free(temp);
//     return temp_data;
// }
// 
// int queue_print(Queue_t *queue)
// {
//     Node_t *prev = queue -> head;
//     while (queue -> head != NULL) {
//         printf("%d\n", queue -> head -> data);
//         prev = queue -> head;
//         queue -> head = queue -> head -> next;
//     }
//     return 0;
// }
// 
// int queue_clean(Queue_t *queue)
// {
//     // while head is not NULL, dequeue
//     while (queue -> head != NULL) {
//         dequeue(queue);
//     }
//     return 0;
// }


Queue_t::Queue_t() : head(NULL), tail(NULL)
{
    std::cout << "Queue created" << std::endl;
    return;
}

Queue_t::Queue_t(Process_t *desired_data)
{
    //this->data = desired_data;
    enqueue(desired_data);
    std::cout << "Queue created with data address of " << head -> data << std::endl;
    //std::cout << "Queue created with head address of " << head -> data << std::endl;
    return;
}

Queue_t::~Queue_t()
{
    std::cout << "Queue destroyed" << std::endl;
}

int Queue_t::enqueue(Process_t *process)
{
    Node_t *temp_node = new Node_t(process);
    if (temp_node == NULL) {
        return 1;
    }
    if (head == NULL) {
        head = temp_node;
        tail = temp_node;
    }
    else {
        // perhaps some sort of "set_next(Node_t *)" setter in Node_t class instead of making data members public
        tail -> next = temp_node;
        tail = temp_node;
    }
    return 0;
}

Process_t *Queue_t::dequeue()
{
    Process_t *temp_data = NULL;
    Node_t *temp_node = NULL;

    if (head == NULL) {
        return temp_data;
    }
    temp_data = head -> data;
    temp_node = head;
    head = head -> next;

    if (head == NULL) {
        tail = NULL;
    }
    //delete temp_node;
    return temp_data;
}

Process_t *Queue_t::top()
{
    // need to overload an operator to be able to print a Process_t using "<<"
    if (head == NULL) {
        return NULL;
    }
    return head -> data;
}

void Queue_t::print()
{
    //Node_t *prev = NULL;
    Node_t *temp_head = head;
    while (temp_head != NULL) {
        std::cout << temp_head -> data -> get_pid() << std::endl;
        //prev = temp_head;
        temp_head = temp_head -> next;
    }
    return;
}
