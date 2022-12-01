#include "list.h"
#include "pcb.h"
#include "process.h"

#include <iostream> // temp
List_t::List_t() : head(nullptr)
{
    std::cout << "list created" << std::endl;
}

List_t::~List_t()
{
    PCB_t *current = head;
    PCB_t *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    std::cout << "list destroyed" << std::endl;
}

/*
int List_t::append(std::string pcb_name, Process_t *data_addr)
{
    PCB_t *temp_head = head;
    PCB_t *temp_pcb = new PCB_t(pcb_name, data_addr);
    if (head == nullptr) {
        head = temp_pcb;
        return 0;
    }
    // else
    while (temp_head->next != nullptr) {
        temp_head = temp_head->next;
    }

    return 0;
}
*/

int List_t::prepend(std::string pcb_name, Process_t *data_addr)
{
    PCB_t *temp_head = head;
    PCB_t *temp_pcb = new PCB_t(pcb_name, data_addr);

    temp_pcb->set_state("New");
    head = temp_pcb;
    temp_pcb->next = temp_head;
    return 0;
}

int List_t::get_waiting_since(Process_t *target)
{
    PCB_t *current = head;
    while (current != nullptr) {
        if (current->p_instance == target) {
            return current->waiting_since;
        }
        current = current->next;
    }
    return -1;
}

int List_t::get_last_run(Process_t *target)
{
    PCB_t *current = head;
    while (current != nullptr) {
        if (current->p_instance == target) {
            return current->last_run;
        }
        current = current->next;
    }
    return 0;
}

std::string List_t::set_pcb_state(Process_t *target, std::string desired_state, int waiting_since, int waiting_on)
{
    PCB_t *current = head;
    while (current != nullptr) {
        if (current->p_instance == target) {
            current->state = desired_state;
            current->waiting_since = waiting_since;
            current->waiting_on = waiting_on;
            return current->pid;
        }
        current = current->next;
    }
    return "Error";
}

std::string List_t::set_last_run(Process_t *target, int last_run)
{
    PCB_t *current = head;
    while (current != nullptr) {
        if (current->p_instance == target) {
            current->last_run = last_run;
        }
        current = current->next;
    }
    return "Error";
}

std::string List_t::remove_pcb(Process_t *target)
{
    PCB_t *current = head;
    PCB_t *prev = head;
    std::string p_name;
    while (current != nullptr) {
        if (current->p_instance == target) {
            p_name = current->pid;
            prev->next = current->next;
            if (current == head) {
                head = nullptr;
            }
            delete current;
            current = nullptr;
            return p_name;
        }
        prev = current;
        current = current->next;
    }
    //delete current->next;
    //std::cout << "Current PCB: " << current->pid << "\nNext PCB: " << current->next->pid << '\n';
    return "error";
}

bool List_t::find(std::string target)
{
    PCB_t *current = head;
    while (current != nullptr) {
        if (current->pid == target) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool List_t::is_empty()
{
    if (head == nullptr) {
        return true;
    }
    return false;
}

PCB_t& List_t::get_pcb(std::string target)
{
    PCB_t *current = head;
    while (current != nullptr) {
        if (current->pid == target) {
            return *current;
        }
        current = current->next;
    }
    throw "Does not exist in the list";
}
/*
std::ostream& List_t::get_pcb(std::ostream& out, std::string target)
{
    PCB_t *current = head;
    while (current != NULL) {
        if (current->pid == target) {
            out << *current;
            return out;
        }
        current = current->next;
    }
    return out;
}
*/

std::ostream& operator<<(std::ostream& out, const List_t& list)
{
    // while not at the end of the list, iterate through each PCB_t object in the list and print it
    PCB_t *current = list.head;
    while (current != NULL) {
        out << *current;
        current = current->next;
    }
    return out;
}
