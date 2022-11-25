#include <vector>
#include <string>

#include "ksim_helpers.h"

int tokenize(std::string buffer, std::vector<std::string> &argv)
{
    int end = 0;
    int start = 0;

    for (end = 0; end < buffer.length(); end++) {
        if (std::isspace(buffer[end]) == 1) {
            continue;
        }
        start = end;
        while (std::isspace(buffer[end]) == 0 && end < buffer.length()) {
            end++;
        }
        argv.push_back(buffer.substr(start, end - start));
    }
    return 0;
}
