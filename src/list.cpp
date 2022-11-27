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
