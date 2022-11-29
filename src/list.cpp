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

    head = temp_pcb;
    temp_pcb->next = temp_head;
    return 0;
}

bool List_t::find(std::string target)
{
    PCB_t *current = head;
    while (current != NULL) {
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
