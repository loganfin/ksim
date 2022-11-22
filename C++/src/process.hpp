#pragma once

class Process_t {
    public:
        Process_t();
        //Process_t(int);
        ~Process_t();
        int get_pid();
    private:
        static int instance_count;
        const int pid;
};
