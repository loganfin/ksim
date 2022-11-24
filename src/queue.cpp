#include "queue.h"

Queue_t::Queue_t(std::string desired_type) : type(desired_type), head(nullptr), tail(nullptr)
{
}

Queue_t::~Queue_t()
{
}
