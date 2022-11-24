#include "kernel.h"

Kernel_t::Kernel_t()
    : new_q("New"), ready_q("Ready"), running_q("Running"), exit_q("Exit"), blocked_q("Blocked")
{
}

Kernel_t::~Kernel_t()
{
}
