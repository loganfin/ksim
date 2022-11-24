#include <iostream>

#include "process.hpp"
#include "state.hpp"

int Process_t::instance_count = 0;

Process_t::Process_t() : next(NULL), pid(instance_count), state()
{
    std::cout << "Process creaed" << std::endl;
    instance_count++;
    return;
}

/*
Process_t::Process_t(int desired_pid) : pid(desired_pid)
{
    std::cout << "Process creaed with PID of " << pid << std::endl;
    return;
}
*/
Process_t::Process_t(State desired_state) : next(NULL), pid(instance_count), state(desired_state)
{
    std::cout << "Process creaed" << std::endl;
    instance_count++;
    return;
}

Process_t::~Process_t()
{
    //delete this;
    std::cout << "Process in " << state <<" destroyed" << std::endl;
    return;
}
