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

#include "process.hpp"
#include "queue.hpp"
//#include "process.h"

// int Process_t::*node_create(int str)
// {
//     Process_t *node = malloc(sizeof(*node));
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
//     Process_t *temp = node_create(data);
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
//     Process_t *temp = node_create(data);
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
//     Process_t *temp = NULL;
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
//     Process_t *prev = queue -> head;
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


Queue_t::Queue_t() : name(""), head(NULL), tail(NULL)
{
    std::cout << "Queue created" << std::endl;
    return;
}

Queue_t::Queue_t(std::string desired_name) : name(desired_name), head(NULL), tail(NULL)
{
    std::cout << "Queue created with name \"" << name << "\"" << std::endl;
    return;
}

/*
int Queue_t::set_name(std::string desired_name)
{
    name = desired_name;
    return 0;
}
*/
/*
Queue_t::Queue_t(Process_t *desired_data)
{
    //this->data = desired_data;
    enqueue(desired_data);
    std::cout << "Queue created with data address of " << head -> data << std::endl;
    //std::cout << "Queue created with head address of " << head -> data << std::endl;
    return;
}
*/

Queue_t::~Queue_t()
{
    Process_t *current = head;
    Process_t *next = NULL;
    std::cout << "destroying " << name << "..." << std::endl;
    while (current != NULL) {
        next = current -> next;
        delete current;
        current = next;
    }
    head = NULL;
    std::cout << "Queue destroyed" << std::endl;
    return;
}

/*
   int Queue_t::enqueue()
   {
   return 0;
   }
   */

int Queue_t::create_process(std::string desired_name)
{
    Process_t *temp_node = new Process_t(desired_name);
    if (temp_node == NULL) {
        return 1;
    }
    if (head == NULL) {
        head = temp_node;
        tail = temp_node;
    }
    else {
        // perhaps some sort of "set_next(Process_t *)" setter in Process_t class instead of making data members public
        tail -> next = temp_node;
        tail = temp_node;
    }
    return 0;
}

int Queue_t::enqueue(Process_t *process)
{
    /*
       Process_t *temp_node = NULL;
       if (process == NULL) {
       temp_node = new Process_t();
       }
       else {
       temp_node = new Process_t(process);
       }
       if (temp_node == NULL) {
       return 1;
       }
       */
    if (head == NULL) {
        head = process;
        tail = process;
    }
    else {
        // perhaps some sort of "set_next(Process_t *)" setter in Process_t class instead of making data members public
        tail -> next = process;
        tail = process;
    }
    return 0;
}

Process_t *Queue_t::detach_head()
{
    Process_t *current = head;
    if (current == NULL) {
        return NULL;
    }
    head = head -> next;
    if (head == NULL) {
        tail = NULL;
    }
    current -> next = NULL;
    return current;
}

int Queue_t::kill_head()
{
    Process_t *current = head;

    if (current == NULL) {
        return 1;
    }
    head = head -> next;
    if (head == NULL) {
        tail = NULL;
    }
    delete current;
    return 0;
}

std::string Queue_t::top()
{
    // need to overload an operator to be able to print a Process_t using "<<"
    if (head == NULL) {
        return NULL;
    }
    return head -> name;
}

void Queue_t::print()
{
    //Process_t *prev = NULL;
    Process_t *temp_head = head;
    while (temp_head != NULL) {
        std::cout << temp_head -> name << std::endl;
        //prev = temp_head;
        temp_head = temp_head -> next;
    }
    return;
}
