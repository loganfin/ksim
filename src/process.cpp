#include "process.h"

#include <iostream> // temp
Process_t::Process_t() : next(nullptr)
{
    //std::cout << "process created" << std::endl;
}

Process_t::~Process_t()
{
    //std::cout << "process destroyed" << std::endl;
}
