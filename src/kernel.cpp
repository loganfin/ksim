#include <iomanip>
#include <iostream>
#include <sstream>

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
    if (p_table.find(pcb_name) == true) {
        return 1;
    }

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

int Kernel_t::io_event(int io_dev_num)
{
    return 0;
}

int Kernel_t::release()
{
    return 0;
}

int Kernel_t::step()
{
    return 0;
}

int Kernel_t::wait(int io_dev_num)
{
    return 0;
}

void Kernel_t::query(std::string target)
{
    // if the target is "all", create a vector of 
    // if a specific target is supplied, find the target in the p_table.
    /*
    if (p_table.head == nullptr) {
        std::cout << "Process \"" << target << "\" not found." << std::endl;
        return;
    }

    if (target == "all") {
    }
    */
    /*
    std::string info = "Process \"" + target + "\" not found.\n";
    if (p_table.find(target) == true) {
        info = "***\n" + p_table.get_info(target) + "***\n";
    }
    return info;
    */
    if (target == "all" && p_table.is_empty() == false) {
        std::cout << p_table;
        return;
    }

    if (p_table.find(target) == true) {
        std::cout << p_table.get_pcb(target);
        return;
    }
    std::cout << "Process \"" << target << "\" not found.\n";
}

int Kernel_t::update_p_table()
{
    return 0;
}

void Kernel_t::prompt()
{
    // use std::ostream?
    std::cout << "ksim-" << std::setfill('0') << std::setw(max_tick_digits) << ticks << "> ";
    //std::cout << "ksim-" << std::setfill('0') << std::setw(max_tick_digits) << ticks << "> ";
    return;
}
