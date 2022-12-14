#pragma once

#include <sstream>
#include <string>

#include "queue.h"
#include "list.h"

enum State {
    blocked_q_0,
    blocked_q_1,
    blocked_q_2,
    blocked_q_3,
    new_q,
    ready_q,
    running_q,
    exit_q,
    total_q
};

class Kernel_t {
    public:
        Kernel_t();
        ~Kernel_t();                            // responsible for deleting Queue_t objects and List_t objects (only if dynamically allocated)
        int add(std::string pcb_name);          // add a process to the "New" queue
        int io_event(int io_dev_num);           // move all processes in the "Blocked" queue that were waiting on io-dev-num to the "Ready" queue
        int release();                          // move running process to the "Exit" queue
        int step();                             // advance the simulation and does various housekeeping tasks
        int wait(int io_dev_num);               // move running process to the "Blocked" queue and set waiting_on in Process_t
        void query(std::string target = "all"); // print information on all processes in the p_table
        void prompt();
    private:
        const int max_ticks = 999999999;
        int ticks;
        List_t p_table;                         // Process table implemented as a linked list
        Queue_t *states;
};
