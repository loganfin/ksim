#pragma once

#include <string>

#include "process.h"

class Queue_t {
    public:
        Queue_t();
        Queue_t(std::string);
        ~Queue_t();
        void set_type(std::string des_type);
        void enqueue(Process_t *data_addr);
        void insert(Process_t *data_addr, int index);
        Process_t *top();
        Process_t *find_at(int index);
        Process_t *dequeue();
        Process_t *kill_head();
        bool is_empty();
        std::string type;
        int length;
    private:
        Process_t *head;
        Process_t *tail;
};

