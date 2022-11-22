#include <iostream>

#include "process.hpp"

int Process_t::instance_count = 0;

Process_t::Process_t() : pid(instance_count)
{
    instance_count++;
    std::cout << "Process creaed" << std::endl;
    return;
}

/*
Process_t::Process_t(int desired_pid) : pid(desired_pid)
{
    std::cout << "Process creaed with PID of " << pid << std::endl;
    return;
}
*/

Process_t::~Process_t()
{
    //delete this;
    std::cout << "Process destroyed" << std::endl;
    return;
}

int Process_t::get_pid()
{
    return pid;
}
