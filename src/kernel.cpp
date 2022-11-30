#include <iomanip>
#include <iostream>
#include <sstream>

#include "kernel.h"
#include "process.h"
#include "list.h"
#include "queue.h"

Kernel_t::Kernel_t()
    : ticks(0)
{
    states = new Queue_t[(int)States::total_q];
    for (int i = (int)States::blocked_q_0; i != (int)States::total_q; i++) {
        switch (i) {
            case 0:
            case 1:
            case 2:
            case 3:
                // overload = operator for queue class
                states[i].set_type("Blocked");
                break;
            case 4:
                states[i].set_type("New");
                break;
            case 5:
                states[i].set_type("Ready");
                break;
            case 6:
                states[i].set_type("Running");
                break;
            case 7:
                states[i].set_type("Exit");
                break;
            default:
                break;
        }
    }
    std::cout << "kernel created" << std::endl;
}

Kernel_t::~Kernel_t()
{
    delete[] states;
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
    states[(int)States::new_q].enqueue(temp_process);
    ticks += 32;
    return 0;
}

int Kernel_t::io_event(int io_dev_num)
{
    ticks += 1;
    // check if any processes exist in the specified blocked queue
    if (states[io_dev_num].is_empty() == true) {
        // if no processes... print "No processes waiting on <io_dev_num>."
        // this error message should move to main.cpp
        std::cout << "No processes waiting on " << io_dev_num << ".\n";
        return 0;
    }
    // if processes exist, move all processes to the ready queue
    std::string p_name;
    Process_t *temp_process;
    while (states[io_dev_num].is_empty() == false) {
        temp_process = states[io_dev_num].dequeue();
        p_name = p_table.set_pcb_state(temp_process, states[(int)States::ready_q].type);
        states[(int)States::ready_q].enqueue(temp_process);
        std::cout << "Process \"" << p_name << "\" moved from " << states[io_dev_num].type << " (iodev=" << io_dev_num << ") to " << states[(int)States::ready_q].type << ".\n";
    }
    return 3;
}

int Kernel_t::release()
{
    // check if any process exists in the running queue
    // if no process exists, return error
    // if process exists, move process to Exit queue and update pcb in p_table
    std::string p_name;
    if (states[(int)States::running_q].is_empty() == true) {
        throw 1;
    }
    Process_t *temp_process = states[(int)States::running_q].dequeue();
    p_name = p_table.set_pcb_state(temp_process, states[(int)States::exit_q].type);
    states[(int)States::exit_q].enqueue(temp_process);
    std::cout << "Process \"" << p_name << "\" moved from " << states[(int)States::running_q].type << " to " << states[(int)States::exit_q].type << ".\n";
    ticks += 32;
    return 0;
}

int Kernel_t::step()
{
    std::string p_name;
    Process_t *temp_process = nullptr;
    PCB_t *temp_pcb = nullptr;
    int temp_ticks = 0;
    int add_ticks = 1;
    int min_ticks_wait = 1024;
    // remove all process in the Exit state
    while (states[(int)States::exit_q].is_empty() == false) {
        temp_process = states[(int)States::exit_q].kill_head();
        p_name = p_table.remove_pcb(temp_process);
        std::cout << "Process \"" << p_name << "\" is banished to the void.\n";
    }
    p_name = "";

    // try to move 1 process from New to Ready
    if (states[(int)States::new_q].is_empty() == false) {
        // need to insert processes into the ready_q based on the last time they were run (least recently run processes to the front)
        // write a queue member function to return a Process_t* of the ith item in the queue (get_p(1))

        // get the Process_t* for the process that is moving from New to Ready (called new_p)
        // then in a loop:
        // starting from head, start getting each Process_t* in the queue (called temp_p)
        // use the Process_t* to look up the corresponding PCB_t in the p_table
        // compare the "last_run" value of new_p and temp_p
        // if "last_run" of new_p PCB_t is less than that of temp_p, insert new_p before temp_p in the queue
        // (need to update set_pcb_state to accomadate "last_run")

        temp_process = states[(int)States::new_q].dequeue();
        p_name = p_table.set_pcb_state(temp_process, states[(int)States::ready_q].type);
        states[(int)States::ready_q].enqueue(temp_process);
        std::cout << "Process \"" << p_name << "\" moved from " << states[(int)States::new_q].type << " to " << states[(int)States::ready_q].type << ".\n";
    }

    // try to advance 1 process from each blocked queue to ready if possible
    for (int i = 0; i < 4; i++) {
        if (states[i].is_empty() == false) {
            // check how long the process in the queue has been waiting
            // if the process has been waiting for longer than 1024 ticks, move to Ready
            temp_process = states[i].top();
            temp_ticks = p_table.get_waiting_since(temp_process);
            std::cout << "test 1" << std::endl;
            if (ticks - temp_ticks >= min_ticks_wait) {
                std::cout << "test 2" << std::endl;
                temp_process = states[i].dequeue();
                p_name = p_table.set_pcb_state(temp_process, states[(int)States::ready_q].type);
                states[(int)States::ready_q].enqueue(temp_process);
                //std::cout << "Process \"" << p_name << "\" moved from " << states[i].type << " to " << states[(int)States::ready_q].type << ".\n";
                std::cout << "Process \"" << p_name << "\" moved from " << states[i].type << " (iodev=" << i << ") to " << states[(int)States::ready_q].type << ".\n";
                continue;
            }
            continue;
            // else, continue and try the other blocked queues
        }
    }

    // move Running process to Ready queue
    if (states[(int)States::running_q].is_empty() == false) {
        temp_process = states[(int)States::running_q].dequeue();
        p_name = p_table.set_pcb_state(temp_process, states[(int)States::ready_q].type);
        states[(int)States::ready_q].enqueue(temp_process);
        std::cout << "Process \"" << p_name << "\" moved from " << states[(int)States::running_q].type << " to " << states[(int)States::ready_q].type << ".\n";
    }
    // try to move 1 process from Ready to Running
    if (states[(int)States::ready_q].is_empty() == false) {
        temp_process = states[(int)States::ready_q].dequeue();
        p_name = p_table.set_pcb_state(temp_process, states[(int)States::running_q].type);
        states[(int)States::running_q].enqueue(temp_process);
        std::cout << "Process \"" << p_name << "\" moved from " << states[(int)States::ready_q].type << " to " << states[(int)States::running_q].type << ".\n";
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
    if (states[(int)States::running_q].is_empty() == true) {
        throw 1;
    }
    Process_t *temp_process = states[(int)States::running_q].dequeue();
    switch (io_dev_num) {
        case (int)States::blocked_q_0:
            p_name = p_table.set_pcb_state(temp_process, states[(int)States::blocked_q_0].type, ticks, (int)States::blocked_q_0);
            states[(int)States::blocked_q_0].enqueue(temp_process);
            std::cout << "Process \"" << p_name << "\" moved from " << states[(int)States::running_q].type << " to " << states[(int)States::blocked_q_0].type << ".\n";
            break;
        case (int)States::blocked_q_1:
            p_name = p_table.set_pcb_state(temp_process, states[(int)States::blocked_q_1].type, ticks, (int)States::blocked_q_1);
            states[(int)States::blocked_q_1].enqueue(temp_process);
            std::cout << "Process \"" << p_name << "\" moved from " << states[(int)States::running_q].type << " to " << states[(int)States::blocked_q_1].type << ".\n";
            break;
        case (int)States::blocked_q_2:
            p_name = p_table.set_pcb_state(temp_process, states[(int)States::blocked_q_2].type, ticks, (int)States::blocked_q_2);
            states[(int)States::blocked_q_2].enqueue(temp_process);
            std::cout << "Process \"" << p_name << "\" moved from " << states[(int)States::running_q].type << " to " << states[(int)States::blocked_q_2].type << ".\n";
            break;
        case (int)States::blocked_q_3:
            p_name = p_table.set_pcb_state(temp_process, states[(int)States::blocked_q_3].type, ticks, (int)States::blocked_q_3);
            states[(int)States::blocked_q_3].enqueue(temp_process);
            std::cout << "Process \"" << p_name << "\" moved from " << states[(int)States::running_q].type << " to " << states[(int)States::blocked_q_3].type << ".\n";
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
