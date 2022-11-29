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
            try {
                ksimOS.release();
            }
            catch (...) {
                std::cout << "No process is currently Running.\n";
            }
            continue;
        }
        else if (argv.at(0) == "step") {
            ksimOS.step();
            continue;
        }
        else if (argv.at(0) == "query") {
            try {
                ksimOS.query(argv.at(1));
                //std::cout << ksimOS.query(argv.at(1));
            }
            catch (...) {
                ksimOS.query();
                //std::cout << ksimOS.query();
            }
            continue;
        }
        /* double arg opcodes */
        else if (argv.at(0) == "add") {
            try {
                if (ksimOS.add(argv.at(1)) == 1) {
                    std::cout << "Process named \"" << argv.at(1) << "\" is already being hosted.\n";
                }
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
                    ksimOS.wait(stoi(argv.at(1)));
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
