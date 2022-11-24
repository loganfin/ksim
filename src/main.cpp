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

    do {
        ksimOS.prompt();
        std::cin >> buffer;
        error = tokenize(buffer, argv);
    } while (argv.at(0) != "exit");
    return 0;
}
