#pragma once

#include "pcb.h"
#include "process.h"

class List_t {
    public:
        List_t();
        ~List_t();

        int prepend(std::string pcb_name, Process_t *data_addr);
        bool find(std::string target);
        bool is_empty();
        PCB_t& get_pcb(std::string target);
        //std::ostream& get_pcb(std::ostream& out, std::string target);
        friend std::ostream& operator<<(std::ostream& out, const List_t& list);
    private:
        PCB_t *head;
};
