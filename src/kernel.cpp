#include <iomanip>
#include <iostream>
#include <sstream>

#include "kernel.h"
#include "process.h"
#include "list.h"
#include "queue.h"

Kernel_t::Kernel_t() : ticks(0)
{
    states = new Queue_t[State::total_q];
    for (int i = State::blocked_q_0; i < State::total_q; i++) {
        // set the type of each queue in the array
        switch (i) {
            case 0:
            case 1:
            case 2:
            case 3:
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
}

Kernel_t::~Kernel_t()
{
    delete[] states;
}

int Kernel_t::add(std::string pcb_name)
{
    Process_t *temp_process = nullptr;

    // process already exists
    if (p_table.find(pcb_name) == true) {
        return 1;
    }

    // create new process with pcb_name
    temp_process = new Process_t;
    if (temp_process == nullptr) {
        return 1;
    }
    // create a process with name: pcb_name and data_addr: temp_process
    p_table.prepend(pcb_name, temp_process);
    // add the process to the back of the new_q
    states[State::new_q].enqueue(temp_process);
    ticks += 32;
    return 0;
}

int Kernel_t::io_event(int io_dev_num)
{
    std::string p_name;
    Process_t *ready_process = nullptr;
    Process_t *blocked_process = nullptr;

    ticks += 1;

    // if no processes exist in specified queue, print error and return
    if (states[io_dev_num].is_empty() == true) {
        std::cout << "No processes waiting on device " << io_dev_num << ".\n";
        return 0;
    }

    // if process(es) exist, move process(es) to the Ready queue and return;
    while (states[io_dev_num].is_empty() == false) {
        for (int i = 0; i < states[io_dev_num].length; i++) {
            ready_process = states[State::ready_q].find_at(i);
            blocked_process = states[io_dev_num].top();
            // if the blocked process was last run longer ago than the current process in the ready queue, insert the blocked process before the ready process
            if (p_table.get_last_run(blocked_process) <= p_table.get_last_run(ready_process)) {
                blocked_process = states[io_dev_num].dequeue();
                p_name = p_table.set_pcb_state(blocked_process, states[State::ready_q].type);
                states[State::ready_q].insert(blocked_process, i);
                std::cout << "Process \"" << p_name << "\" moved from " << states[io_dev_num].type << " (iodev=" << io_dev_num << ") to " << states[State::ready_q].type << ".\n";
                break;
            }
            // if on the last element in the Blocked queue or if the Ready queue is empty, enqueue current process to the Ready queue
            if (i == states[io_dev_num].length - 1 || states[State::ready_q].is_empty() == true) {
                blocked_process = states[io_dev_num].dequeue();
                p_name = p_table.set_pcb_state(blocked_process, states[State::ready_q].type);
                states[State::ready_q].enqueue(blocked_process);
                std::cout << "Process \"" << p_name << "\" moved from " << states[io_dev_num].type << " (iodev=" << io_dev_num  << ") to " << states[State::ready_q].type << ".\n";
                break;
            }
        }
    }
    return 0;
}

int Kernel_t::release()
{
    std::string p_name;
    Process_t *temp_process = nullptr;

    // if no process exists in the Running queue, return
    if (states[State::running_q].is_empty() == true) {
        throw 1;
    }

    // move the Running process to Exit queue
    temp_process = states[State::running_q].dequeue();
    p_name = p_table.set_pcb_state(temp_process, states[State::exit_q].type);
    p_table.set_last_run(temp_process, ticks);
    states[State::exit_q].enqueue(temp_process);
    std::cout << "Process \"" << p_name << "\" moved from " << states[State::running_q].type << " to " << states[State::exit_q].type << ".\n";
    ticks += 32;
    return 0;
}

int Kernel_t::step()
{
    std::string p_name;
    Process_t *temp_process = nullptr;
    Process_t *new_process = nullptr;
    int temp_ticks = 0;
    int add_ticks = 1;
    int min_ticks_wait = 1024;

    // remove all process in the Exit state
    while (states[State::exit_q].is_empty() == false) {
        temp_process = states[State::exit_q].kill_head();
        p_name = p_table.remove_pcb(temp_process);
        std::cout << "Process \"" << p_name << "\" is banished to the void.\n";
    }
    p_name = "";

    // try to move 1 process from New to Ready
    if (states[State::new_q].is_empty() == false) {
        for (int i = 0; i < states[State::new_q].length; i++) {
            temp_process = states[State::ready_q].find_at(i);
            new_process = states[State::new_q].top();
            if (p_table.get_last_run(new_process) <= p_table.get_last_run(temp_process)) {
                new_process = states[State::new_q].dequeue();
                p_name = p_table.set_pcb_state(new_process, states[State::ready_q].type);
                states[State::ready_q].insert(new_process, i);
                std::cout << "Process \"" << p_name << "\" moved from " << states[State::new_q].type << " to " << states[State::ready_q].type << ".\n";
                break;
            }
        }
    }

    // try to advance 1 process from each blocked queue to ready if possible
    for (int i = 0; i < 4; i++) {
        if (states[i].is_empty() == false) {
            temp_process = states[i].top();
            temp_ticks = p_table.get_waiting_since(temp_process);
            // if the process has been waiting for longer than 1024 ticks, move to Ready
            if (ticks - temp_ticks >= min_ticks_wait) {
                for (int j = 0; j < states[i].length; j++) {
                    temp_process = states[State::ready_q].find_at(j);
                    new_process = states[i].top();
                    if (p_table.get_last_run(new_process) <= p_table.get_last_run(temp_process)) {
                        new_process = states[i].dequeue();
                        p_name = p_table.set_pcb_state(new_process, states[State::ready_q].type);
                        states[State::ready_q].insert(new_process, j);
                        std::cout << "Process \"" << p_name << "\" moved from " << states[i].type << " (iodev=" << i << ") to " << states[State::ready_q].type << ".\n";
                        break;
                    }
                    if (j == states[i].length - 1 || states[State::ready_q].is_empty() == true) {
                        temp_process = states[i].dequeue();
                        p_name = p_table.set_pcb_state(temp_process, states[State::ready_q].type);
                        states[State::ready_q].enqueue(temp_process);
                        std::cout << "Process \"" << p_name << "\" moved from " << states[i].type << " (iodev=" << i << ") to " << states[State::ready_q].type << ".\n";
                        break;
                    }
                }
                continue;
            }
            continue;
        }
    }

    // move Running process to Ready queue
    if (states[State::running_q].is_empty() == false) {
        temp_process = states[State::running_q].dequeue();
        p_name = p_table.set_pcb_state(temp_process, states[State::ready_q].type);
        p_table.set_last_run(temp_process, ticks);
        states[State::ready_q].enqueue(temp_process);
        std::cout << "Process \"" << p_name << "\" moved from " << states[State::running_q].type << " to " << states[State::ready_q].type << ".\n";
    }

    // try to move 1 process from Ready to Running
    if (states[State::ready_q].is_empty() == false) {
        temp_process = states[State::ready_q].dequeue();
        p_name = p_table.set_pcb_state(temp_process, states[State::running_q].type);
        states[State::running_q].enqueue(temp_process);
        std::cout << "Process \"" << p_name << "\" moved from " << states[State::ready_q].type << " to " << states[State::running_q].type << ".\n";
        add_ticks = 256;
    }

    ticks += add_ticks;
    return 0;
}

int Kernel_t::wait(int io_dev_num)
{
    // check if a process exists in the running queue
    // if no process, return error
    std::string p_name;
    Process_t *temp_process = nullptr;

    // if no process in the Running queue, return
    if (states[State::running_q].is_empty() == true) {
        throw 1;
    }

    // if process exists in Running queue, move it to the corresponding io-dev-num queue
    temp_process = states[State::running_q].dequeue();
    p_name = p_table.set_pcb_state(temp_process, states[io_dev_num].type, ticks, io_dev_num);
    states[io_dev_num].enqueue(temp_process);
    std::cout << "Process \"" << p_name << "\" moved from " << states[State::running_q].type << " to " << states[io_dev_num].type << ".\n";
    p_table.set_last_run(temp_process, ticks);
    ticks += 1;
    return 0;
}

void Kernel_t::query(std::string target)
{
    if (target == "all") {
        if (p_table.is_empty() == true) {
            std::cout << "No processes being hosted.\n";
            return;
        }
        // else ...
        std::cout << p_table;
        return;
    }

    if (p_table.find(target) == true) {
        std::cout << p_table.get_pcb(target);
        return;
    }

    std::cout << "Process \"" << target << "\" not found.\n";
    return;
}

void Kernel_t::prompt()
{
    int max_tick_digits = std::to_string(max_ticks).size();
    // rollover mechanism
    if (ticks > max_ticks) {
        ticks = ticks - max_ticks - 1;
    }
    std::cout << "ksim-" << std::setfill('0') << std::setw(max_tick_digits) << ticks << "> ";
    return;
}
