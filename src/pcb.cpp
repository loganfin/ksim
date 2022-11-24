#include "pcb.h"
#include "process.h"

PCB_t::PCB_t(std::string desired_pid, Process_t *desired_instance)
    : next(nullptr), p_instance(desired_instance), pid(desired_pid), waiting_on(-1), waiting_since(-1)
{
}

PCB_t::~PCB_t()
{
}
