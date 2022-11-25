#include <iomanip>
#include <iostream>

#include "kernel.h"

Kernel_t::Kernel_t()
    : ticks(0), new_q("New"), ready_q("Ready"), running_q("Running"), exit_q("Exit"), blocked_q("Blocked")
{
}

Kernel_t::~Kernel_t()
{
}

void Kernel_t::prompt()
{
    std::cout << "ksim-" << std::setfill('0') << std::setw(max_tick_digits) << ticks << "> ";
    return;
}
