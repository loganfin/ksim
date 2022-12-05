#pragma once

/* equivalent to a queue node */
class Process_t {
    public:
        Process_t();
        ~Process_t();
        Process_t *next;     // the next Process_t instance in the queue
    private:
};

