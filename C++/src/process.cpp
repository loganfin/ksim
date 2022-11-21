#include <iostream>

#include "process.hpp"

Process_t::Process_t() : pid(0)
{
    std::cout << "Process creaed" << std::endl;
}

Process_t::Process_t(int desired_pid) : pid(desired_pid)
{
    std::cout << "Process creaed with PID of " << pid << std::endl;
}

Process_t::~Process_t()
{
    std::cout << "Process destroyed" << std::endl;
}

int Process_t::get_pid()
{
    return pid;
}
