#pragma once

#include <string>

#include "queue.h"
#include "list.h"

class Kernel_t {
    public:
        Kernel_t();
        ~Kernel_t();                    // responsible for deleting Queue_t objects and List_t objects (only if dynamically allocated)

        int add(std::string);           // add a process to the "New" queue
        int io_event(int);              // move all processes in the "Blocked" queue that were waiting on io-dev-num to the "Ready" queue
        int release();                  // move running process to the "Exit" queue
        int step();                     // advance the simulation and does various housekeeping tasks
        int wait(int);                  // move running process to the "Blocked" queue and set waiting_on in Process_t
        int query(std::string = "all"); // print information on all processes in the p_table

        int update_p_table();           // update the proper PCB_t object in p_table with the relevant information
        std::string prompt();
    private:
        // maybe Hash_t p_table;
        int ticks;
        List_t p_table;
        Queue_t new_q;
        Queue_t ready_q;
        Queue_t running_q;
        Queue_t exit_q;
        Queue_t blocked_q;
};
