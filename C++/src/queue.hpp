#pragma once

#include <string>

#include "process.hpp"

class Queue_t {
    public:
        Queue_t();
        Queue_t(std::string);
        //Queue_t(Process_t *);
        ~Queue_t();
        //int set_name(std::string);
        int create_process(std::string);
        Process_t *detach_head();
        int enqueue(Process_t *);
        int kill_head();
        std::string top();
        void print();
    private:
        std::string name;
        Process_t *head;
        Process_t *tail;
};
