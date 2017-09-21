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

    JackTokeniser token_machine(argv[1]);
    while (token_machine.hasMoreTokens()) {
        std::cout << "Token found : " << token_machine.getToken() << " - "
                  << static_cast<int>(token_machine.getTokenType()) << "\n";
        token_machine.showState();
        token_machine.advance();
    }

    std::cerr << "The rest is to be implemented by us \n";

    return 0;
}
