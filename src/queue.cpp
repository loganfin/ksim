#include "queue.h"

#include <iostream> // temp
Queue_t::Queue_t(std::string desired_type) : type(desired_type), head(nullptr), tail(nullptr)
{
    std::cout << "queue with type \"" << type << "\" created" << std::endl;
}

Queue_t::~Queue_t()
{
    Process_t *current = head;
    Process_t *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    std::cout << "queue with type \"" << type << "\" destroyed" << std::endl;
}

void Queue_t::enqueue(Process_t *data_addr)
{
    if (head == nullptr) {
        head = data_addr;
        tail = data_addr;
    }
    else {
        tail->next = data_addr;
        tail = data_addr;
    }
    return;
}

Process_t *Queue_t::dequeue()
{
    Process_t *current = head;
    if (current == nullptr) {
        return nullptr;
    }
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    current->next = nullptr;
    return current;
}

Process_t *Queue_t::kill_head()
{
    Process_t *current = head;
    if (current == nullptr) {
        return nullptr;
    }
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete current;
    return current;
}

bool Queue_t::is_empty()
{
    if (head == nullptr) {
        return true;
    }
    return false;
}
