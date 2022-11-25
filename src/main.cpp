#include <iostream>
#include <string>
#include <vector>

#include "kernel.h"
#include "ksim_helpers.h"

int main()
{
    int error;
    Kernel_t ksimOS;
    std::string buffer;
    std::vector<std::string> argv;

    while (1) {
        argv.clear();
        ksimOS.prompt();
        getline(std::cin, buffer);
        error = tokenize(buffer, argv);
        if (argv.size() == 0) {
            continue;
        }
        /* single arg opcodes */
        if (argv.at(0) == "exit") {
            break;
        }
        else if (argv.at(0) == "release") {
            std::cout << "release" << std::endl;
            continue;
        }
        else if (argv.at(0) == "step") {
            std::cout << "step" << std::endl;
            continue;
        }
        else if (argv.at(0) == "query") {
            std::cout << "query" << std::endl;
            continue;
        }
        /* double arg opcodes */
        else if (argv.at(0) == "add") {
            std::cout << "add" << std::endl;
            continue;
        }
            /* io-dev-num opcodes*/
        else if (argv.at(0) == "io-event") {
            try {
                if (std::stoi(argv.at(1)) > -1 && std::stoi(argv.at(1)) < 4) {
                    std::cout << "io-event" << std::endl;
                    continue;
                }
            }
            catch (...) {
            }
            std::cout << "Opcode \"" << argv.at(0) << "\" requires an integer operand in the range [0,3].\n";
            continue;
        }
        else if (argv.at(0) == "wait") {
            try {
                if (std::stoi(argv.at(1)) > -1 && std::stoi(argv.at(1)) < 4) {
                    std::cout << "wait" << std::endl;
                    continue;
                }
            }
            catch (...) {
            }
            std::cout << "Opcode \"" << argv.at(0) << "\" requires an integer operand in the range [0,3].\n";
            continue;
        }
        else {
            std::cout << "Invalid opcode.\n";
        }
    }
    std::cout << "Exiting...\n";
    return 0;
}
