#include <iostream>

#include "node.hpp"
#include "process.hpp"

Node_t::Node_t() : data(NULL), next(NULL)
{
    std::cout << "Node created" << std::endl;
}

Node_t::Node_t(Process_t *desired_data)
{
    data = desired_data;
    std::cout << "Node created with data address of " << data << std::endl;
}

Node_t::~Node_t()
{
    delete this;
    std::cout << "Node destroyed" << std::endl;
}
