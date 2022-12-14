#pragma once

#include <string>

#include "process.h"

/* equivalent to a linked list node */
class PCB_t {
    public:
        PCB_t() = delete;
        PCB_t(std::string desired_pid, Process_t *desired_instance);
        ~PCB_t();
        int set_state(std::string desired_state);
        PCB_t *next;                    // the next PCB_t in the p_table
        Process_t *const p_instance;    // the value of p_instance shouldn't change (should always point to the same p_instance)
        const std::string pid;          // the name of the process assigned in the constructor
        std::string state;              // the type of Queue_t that p_instance currently resides in
        int waiting_on;                 // the io_dev_num of the device the process is currently waiting on, = -1 if not currently blocked
        int waiting_since;              // the tick that the process was blocked on, = -1 if not currently blocked
        int last_run;                   // stores the tick value of the last run
        friend std::ostream& operator<<(std::ostream& out, const PCB_t& pcb);
    private:
};

