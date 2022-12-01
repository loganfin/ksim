#pragma once

#include "pcb.h"
#include "process.h"

class List_t {
    public:
        List_t();
        ~List_t();

        int prepend(std::string pcb_name, Process_t *data_addr);
        int get_waiting_since(Process_t *target);
        int get_last_run(Process_t *target);
        std::string set_pcb_state(Process_t *target, std::string desired_state, int waiting_since = -1, int io_dev_num = -1);
        std::string set_last_run(Process_t *target, int last_run);
        std::string remove_pcb(Process_t *target);
        bool find(std::string target);
        bool is_empty();
        PCB_t& get_pcb(std::string target);
        //std::ostream& get_pcb(std::ostream& out, std::string target);
        friend std::ostream& operator<<(std::ostream& out, const List_t& list);
    private:
        PCB_t *head;
};
