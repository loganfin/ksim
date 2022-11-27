#include <iostream>
#include <string>
#include <vector>

#include "kernel.h"
#include "ksim_helpers.h"

int main()
{
    Kernel_t ksimOS;
    std::string buffer;
    std::vector<std::string> argv;

    while (1) {
        argv.clear();
        ksimOS.prompt();
        getline(std::cin, buffer);
        tokenize(buffer, argv); // try catch block here?
        if (argv.size() == 0) {
            continue;
        }
        /* single arg opcodes */
        if (argv.at(0) == "exit") {
            std::cout << "Exiting...\n";
            break;
            // return 0; //?
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
            try {
                ksimOS.add(argv.at(1));
                std::cout << "add" << std::endl;
                //continue;
            }
            catch (...) {
                std::cout << "Opcode \"" << argv.at(0) << "\" requires one operand.\n";
            }
            continue;
        }
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
    return 0;
}
