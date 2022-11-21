#pragma once

#include "process.hpp"

class Node_t {
    public:
        Node_t();
        Node_t(Process_t *);
        ~Node_t();
        Process_t *data;
        Node_t *next;
    private:
};
