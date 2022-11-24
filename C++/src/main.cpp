#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "ksim.hpp"
#include "list.hpp"

/*
int main(void)
{
    printf("Welcome to KSIM!\n");
    return ksim_loop();
}
*/

//first way
/*
int main(void)
{
    std::vector<std::string> queue_names = {
        "New",
        "Ready",
        "Running",
        "Exit",
        "Blocked"
    };
    List_t process_table(queue_names);
    std::string buffer;
    std::vector<std::string> argv;
    while (argv[0] != "exit") {
        switch (argv[0]) {
            case "add":
                break;
            case "query":
                process_table.query(argv[1]);
                break;
            case "io-event":
                break;
            case "release":
                break;
            default:
                break;
        };
        process_table.add_process(buffer);
    }
    return 0;
}
*/
/*
#include "queue.hpp"

int main(void)
{
    Queue_t states[STATE_TOTAL];
}
*/

std::string prompt(int ticks);
int tokenize(std::string buffer, std::vector<std::string> argv);

int main()
{
    const int max_ticks = 999999999;
    const int max_tick_digits = 9;

    int ticks = 0;
    std::string buffer;
    std::vector<std::string> argv;
    std::vector<std::string> queue_names = {
        "New",
        "Ready",
        "Running",
        "Exit",
        "Blocked"
    };
    List_t process_table(queue_names);

    while (argv[0] != "exit") {
        std::cout << prompt(ticks);
        std::cout << std::setfill('0') << std::setw(max_tick_digits) << ticks;
        std::cin >> buffer;
        tokenize(buffer, argv);
        if (ticks > max_ticks) {
            ticks = ticks - max_ticks;
        }
    }
}

int tokenize(std::string buffer, std::vector<std::string> argv)
{
    return 0;
}
