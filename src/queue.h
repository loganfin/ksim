#pragma once

#include <string>

#include "process.h"

class Queue_t {
    public:
        Queue_t() = delete;             // every Queue_t object must have a type initalized in the constructor
        Queue_t(std::string);
        ~Queue_t();

        void enqueue(Process_t *data_addr);
        Process_t *dequeue();
        Process_t *kill_head();
        bool is_empty();
    private:
        const std::string type;
        Process_t *head;
        Process_t *tail;
};

