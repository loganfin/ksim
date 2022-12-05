#include "queue.h"

Queue_t::Queue_t() : length(0), head(nullptr), tail(nullptr)
{
}

Queue_t::~Queue_t()
{
    Process_t *current = head;
    Process_t *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        length--;
        current = next;
    }
    head = nullptr;
}

void Queue_t::set_type(std::string des_type)
{
    type = des_type;
    return;
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
    length++;
    return;
}

void Queue_t::insert(Process_t *data_addr, int index)
{
    Process_t *current = head;
    Process_t *prev = nullptr;
    if (head == nullptr) {
        enqueue(data_addr);
        return;
    }
    for (int i = index; i > 0; i--) {
        prev = current;
        current = current->next;
    }
    data_addr->next = current;

    if (prev == nullptr) {
        head = data_addr;
    }
    else {
        prev->next = data_addr;
    }

    return;
}

Process_t *Queue_t::top()
{
    return head;
}

Process_t *Queue_t::find_at(int index)
{
    Process_t *current = head;
    for (int i = index; i > 0; i--) {
        current = current->next;
        if (current == nullptr) {
            return nullptr;
        }
    }
    return current;
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
    length--;
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
    length--;
    return current;
}

bool Queue_t::is_empty()
{
    if (head == nullptr) {
        return true;
    }
    return false;
}
