#include <iomanip>
#include <iostream>
#include <sstream>

#include "kernel.h"
#include "process.h"
#include "list.h"
#include "queue.h"

Kernel_t::Kernel_t()
    : ticks(0), new_q("New"), ready_q("Ready"), running_q("Running"), exit_q("Exit"), blocked_q_0("Blocked"), blocked_q_1("Blocked"), blocked_q_2("Blocked"), blocked_q_3("Blocked")
{
    std::cout << "kernel created" << std::endl;
}

Kernel_t::~Kernel_t()
{
    std::cout << "kernel destroyed" << std::endl;
}

int Kernel_t::add(std::string pcb_name)
{
    // process already exists
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
    // check if any process exists in the running queue
    // if no process exists, return error
    // if process exists, move process to Exit queue and update pcb in p_table
    std::string p_name;
    if (running_q.is_empty() == true) {
        throw 1;
    }
    Process_t *temp_process = running_q.dequeue();
    p_name = p_table.set_pcb_state(temp_process, "Exit");
    exit_q.enqueue(temp_process);
    std::cout << "Process \"" << p_name << "\" moved from Running to Exit.\n";
    ticks += 32;
    return 0;
}

int Kernel_t::step()
{
    std::string p_name;
    Process_t *temp_process = nullptr;
    int add_ticks = 1;
    // remove all process in the Exit state
    while (exit_q.is_empty() == false) {
        temp_process = exit_q.kill_head();
        p_name = p_table.remove_pcb(temp_process);
        std::cout << "Process \"" << p_name << "\" is banished to the void.\n";
    }
    p_name = "";

    // try to move 1 process from New to Ready
    if (new_q.is_empty() == false) {
        temp_process = new_q.dequeue();
        p_name = p_table.set_pcb_state(temp_process, "Ready");
        ready_q.enqueue(temp_process);
        std::cout << "Process \"" << p_name << "\" moved from " << new_q.type << " to " << ready_q.type << ".\n";
    }
    // try to advance 1 process from blocked to ready if possible
    // move Running process to Ready queue
    if (running_q.is_empty() == false) {
        temp_process = running_q.dequeue();
        p_name = p_table.set_pcb_state(temp_process, "Ready");
        ready_q.enqueue(temp_process);
        std::cout << "Process \"" << p_name << "\" moved from Running to Ready.\n";
    }
    // try to move 1 process from Ready to Running
    if (ready_q.is_empty() == false) {
        temp_process = ready_q.dequeue();
        p_name = p_table.set_pcb_state(temp_process, "Running");
        running_q.enqueue(temp_process);
        std::cout << "Process \"" << p_name << "\" moved from Ready to Running.\n";
        add_ticks = 256;
    }
    ticks += add_ticks;
    return 0;
}

int Kernel_t::wait(int io_dev_num)
{
    // check if a process exists in the running queue
    // if no process, return error
    // if process, move to specific blocked queue and update p_table
    std::string p_name;
    if (running_q.is_empty() == true) {
        throw 1;
    }
    Process_t *temp_process = running_q.dequeue();
    switch (io_dev_num) {
        case 0:
            p_name = p_table.set_pcb_state(temp_process, blocked_q_0.type, ticks, 0);
            blocked_q_0.enqueue(temp_process);
            std::cout << "Process \"" << p_name << "\" moved from " << running_q.type << " to " << blocked_q_0.type << ".\n";
            break;
        case 1:
            p_name = p_table.set_pcb_state(temp_process, blocked_q_1.type, ticks, 1);
            blocked_q_1.enqueue(temp_process);
            std::cout << "Process \"" << p_name << "\" moved from " << running_q.type << " to " << blocked_q_1.type << ".\n";
            break;
        case 2:
            p_name = p_table.set_pcb_state(temp_process, blocked_q_2.type, ticks, 2);
            blocked_q_2.enqueue(temp_process);
            std::cout << "Process \"" << p_name << "\" moved from " << running_q.type << " to " << blocked_q_2.type << ".\n";
            break;
        case 3:
            p_name = p_table.set_pcb_state(temp_process, blocked_q_3.type, ticks, 3);
            blocked_q_3.enqueue(temp_process);
            std::cout << "Process \"" << p_name << "\" moved from " << running_q.type << " to " << blocked_q_3.type << ".\n";
            break;
        default:
            break;
    }
    ticks += 1;
    return 0;
}

void Kernel_t::query(std::string target)
{
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
