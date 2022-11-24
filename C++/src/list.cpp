#include <iostream>
#include <vector>
#include <string>

#include "list.hpp"
#include "queue.hpp"

List_t::List_t(std::vector<std::string> desired_queue_names) : num_queues(desired_queue_names.size()), head(NULL), tail(NULL)
{
    states = new Queue_t[num_queues];
    for (int i = 0; i < desired_queue_names.size(); i++) {
        states[i].set_type(desired_queue_names.at(i));
    }
}

List_t::~List_t()
{
    delete[] states;
}

int List_t::add_pcb(std::string desired_pid)
{
    // allocate memory for a new process
    // create a PCB_t pointer to store process information in linked list
    PCB_t *new_process = new PCB_t(desired_pid);
    if (new_process == NULL) {
        return 1;
    }
    // create a Process_t pointer in the STATE_NEW queue
    new_process -> memory_space = states[STATE_NEW].spawn_process();
    if (head == NULL) {
        head = new_process;
        tail = new_process;
    }
    else {
        tail -> next = new_process;
        tail= new_process;
    }
    //states[STATE_NEW].spawn_process(desired_pid);
    return 0;
}

void List_t::query(std::string process_name)
{
    PCB_t *current_pcb = head;
    while (current_pcb != NULL) {
        if (process_name == current_pcb -> pid) {
            std::cout << "***\n";
            std::cout << "\tid: \"" << current_pcb -> pid << "\"\n";
            std::cout << "\tstate: \"" << current_pcb -> memory_space -> state << "\"\n";
            std::cout << "***\n";
        }
    }
}
