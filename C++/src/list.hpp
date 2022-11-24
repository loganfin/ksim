#include <vector>
#include "node.hpp"
#include "queue.hpp"
#include "state.hpp"

class PCB_t {
    public:
        PCB_t();
        PCB_t(std::string);
        ~PCB_t();

        PCB_t *next;                // the next link in the list
        std::string pid;            // the name of the process
        std::string state;          // the name of the queue the process currently exists in
        Process_t *memory_space;    // the simulated location of the process in memory
        int waiting_on;             // the io_dev_num of the device it is waiting on
        int waiting_since;          // the tick the process has been waiting since
    private:
};

class List_t {
    public:
        List_t(std::vector<std::string>);
        ~List_t();
        int add_pcb(std::string);
        void query(std::string = "all");
    private:
        const int num_queues;
        Queue_t *states;
        PCB_t *head;
        PCB_t *tail;
};
