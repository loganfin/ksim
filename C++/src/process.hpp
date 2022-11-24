#pragma once

#include <string>
#include "state.hpp"

class Process_t {
    public:
        Process_t();
        //Process_t(int);
        Process_t(std::string);
        ~Process_t();
        //int get_pid();

        Process_t *next;

        static int instance_count;
        const int pid;
        std::string state;
    private:
};
