#pragma once

#include <string>

#include "process.hpp"
#include "state.hpp"

class Queue_t {
    public:
        Queue_t();
        Queue_t(std::string);
        //Queue_t(Process_t *);
        ~Queue_t();
        //int set_name(std::string);

        Process_t *spawn_process();
        Process_t *detach_head();
        int enqueue(Process_t *);
        int kill_head();
        std::string top();
        void print();
        int set_type(std::string);
    private:
        std::string type;
        Process_t *head;
        Process_t *tail;
};
