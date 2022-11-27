#include "pcb.h"
#include "process.h"

#include <iostream> // temp
PCB_t::PCB_t(std::string desired_pid, Process_t *desired_instance)
    : next(nullptr), p_instance(desired_instance), pid(desired_pid), waiting_on(-1), waiting_since(-1)
{
    std::cout << "pcb with pid \"" << pid << "\" created" << std::endl;
}

PCB_t::~PCB_t()
{
    std::cout << "pcb with pid \"" << pid << "\" destroyed" << std::endl;
}
