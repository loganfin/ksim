#include <iomanip>
#include <iostream>

#include "kernel.h"
#include "process.h"
#include "list.h"
#include "queue.h"

Kernel_t::Kernel_t()
    : ticks(0), new_q("New"), ready_q("Ready"), running_q("Running"), exit_q("Exit"), blocked_q("Blocked")
{
    std::cout << "kernel created" << std::endl;
}

Kernel_t::~Kernel_t()
{
    std::cout << "kernel destroyed" << std::endl;
}

int Kernel_t::add(std::string pcb_name)
{
    //p_table.prepend(pcb_name, new_q.enqueue());
    Process_t *temp_process = new Process_t;
    if (temp_process == nullptr) {
        return 1;
    }
    if (p_table.prepend(pcb_name, temp_process) ==  1) {
        return 1;
    }
    new_q.enqueue(temp_process);
    ticks += 32;
    return 0;
}

void Kernel_t::prompt()
{
    std::cout << "ksim-" << std::setfill('0') << std::setw(max_tick_digits) << ticks << "> ";
    return;
}
