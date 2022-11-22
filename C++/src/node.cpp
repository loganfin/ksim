#include <iostream>

#include "node.hpp"
#include "process.hpp"

Node_t::Node_t() : data(NULL), next(NULL)
{
    // should each node be forced to have a valid process?
    std::cout << "Node created" << std::endl;
    data = new Process_t;
}

Node_t::Node_t(Process_t *desired_data)
{
    std::cout << "Node created with data address of " << data << std::endl;
    data = desired_data;
}

Node_t::~Node_t()
{
    std::cout << "Node destroyed" << std::endl;
    delete data;
    //delete this;
}
