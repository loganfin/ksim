#include <iostream>

#include "process.hpp"

int Process_t::instance_count = 0;

Process_t::Process_t() : next(NULL), pid(instance_count), name(std::to_string(pid))
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
Process_t::Process_t(std::string desired_name) : next(NULL), pid(instance_count), name(desired_name)
{
    std::cout << "Process creaed" << std::endl;
    instance_count++;
    return;
}

Process_t::~Process_t()
{
    //delete this;
    std::cout << "Process " << name <<" destroyed" << std::endl;
    return;
}
