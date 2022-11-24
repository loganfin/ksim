#pragma once

#include "pcb.h"

class List_t {
    public:
        List_t();
        ~List_t();
    private:
        PCB_t *head;
};
