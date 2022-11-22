#include <iostream>
#include <stdio.h>

#include "ksim.hpp"
#include "process.hpp"
#include "queue.hpp"

/* 5 states:
 * 1. new
 * 2. ready (queue)
 * 3. running
 * 4. blocked (queue)
 * 5. exit
 */

int find(Queue_t [], std::string);

const int num_queues = 5;

int ksim_loop(void)
{
    int error = 0;

    //Queue_t queue_list[num_queues];
    Queue_t new_q("New");
    Queue_t ready_q("Ready");
    Queue_t running_q("Running");
    Queue_t blocked_q("Blocked");
    Queue_t exit_q("Exit");

    new_q.create_process("one");
    new_q.create_process("two");
    new_q.create_process("three");
    std::cout << "new_q:" << std::endl;
    new_q.print();
    running_q.enqueue(new_q.detach_head());
    std::cout << "new_q:" << std::endl;
    new_q.print();
    std::cout << "running_q:" << std::endl;
    running_q.print();
    //new_q.enqueue();
    //new_q.enqueue();
    new_q.kill_head();


    /*
    Process_t *temp_process = NULL;
    //Process_t *two_p = new Process_t(2);

    //temp_process = new Process_t;
    new_q.enqueue();
    //temp_process = new Process_t;
    new_q.enqueue();
    new_q.print();
    temp_process = new_q.top();
    std::cout << "top of new_q is " << temp_process->get_pid() << std::endl;
    new_q.dequeue();
    new_q.print();
    temp_process = new_q.top();
    std::cout << "top of new_q is " << temp_process->get_pid() << std::endl;

    ready_q.enqueue(new_q.dequeue());
    new_q.print();
    ready_q.print();
    */

    return error;
}

/*
int ksim_loop(void)
{
    int error = 0;
    Queue_t *ready = queue_create();
    Queue_t *blocked = queue_create();
    Process_t one(1);

    enqueue(ready, 2);
    enqueue(ready, 3);
    enqueue(ready, 4);

    enqueue(blocked, dequeue(ready));

    printf("ready queue\n");
    queue_print(ready);
    printf("blocked queue\n");
    queue_print(blocked);

    queue_clean(ready);
    queue_clean(blocked);
    return error;
}
*/

int find(Queue_t queue_list[], std::string target)
{
    // bool found = false;
    // for (int i = 0; i < num_queues; i++) {
    //     found = queue_list[i].find(target);
    //     if (found == true) {
    //         return true;
    //     }
    // }
    // return false
    return 0;
}
