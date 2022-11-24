#pragma once

#include <string>

#include "process.h"

class Queue_t {
    public:
        Queue_t() = delete;             // every Queue_t object must have a type initalized in the constructor
        Queue_t(std::string);
        ~Queue_t();
    private:
        const std::string type;
        Process_t *head;
        Process_t *tail;
};

