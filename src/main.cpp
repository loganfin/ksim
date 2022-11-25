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

        if (argv.size() > 1) {
            /* double arg opcodes */
            if (argv.at(0) == "add") {
                std::cout << "add" << std::endl;
                continue;
            }
            else if (argv.at(0) == "io-event") {
                if (std::stoi(argv.at(1)) < 0 || std::stoi(argv.at(1)) > 3) {
                    std::cout << "Opcode \"" << argv.at(0) << "\" requires an operand in the range [0,3].\n";
                    continue;
                }
                std::cout << "io-event" << std::endl;
                continue;
            }
            else if (argv.at(0) == "wait") {
                if (std::stoi(argv.at(1)) < 0 || std::stoi(argv.at(1)) > 3) {
                    std::cout << "Opcode \"" << argv.at(0) << "\" requires an operand in the range [0,3].\n";
                    continue;
                }
                std::cout << "wait" << std::endl;
                continue;
            }
        }
        else {
            std::cout << "Opcode \"" << argv.at(0) << "\" requires 1 operand.\n";
            continue;
        }
    }
    return 0;
}
