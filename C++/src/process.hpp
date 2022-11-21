#pragma once

class Process_t {
    public:
        Process_t();
        Process_t(int);
        ~Process_t();
        int get_pid();
    private:
        const int pid;
};
