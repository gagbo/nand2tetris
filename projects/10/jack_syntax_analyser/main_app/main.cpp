#include <iostream>
#include "tokeniser/tokeniser.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Print usage and exit because wrong number of arguments\n";
        return 1;
    } else {
        std::string argument = argv[1];
        std::cout << "Parsed argument : " << argument << "\n";
    }
    std::cerr << "To be implemented by us \n";

    return 0;
}
