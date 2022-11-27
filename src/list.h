#pragma once

#include "pcb.h"
#include "process.h"

class List_t {
    public:
        List_t();
        ~List_t();

        int prepend(std::string pcb_name, Process_t *data_addr);
    private:
        PCB_t *head;
};
