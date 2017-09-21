#include <boost/filesystem.hpp>  // Is included in std=c++17
#include <iostream>
#include <string>
#include <vector>

#include "tokeniser/tokeniser.h"

void parse_arguments(int argc, char** argv,
                     std::vector<std::string>& files_list);

int main(int argc, char** argv) {
    std::vector<std::string> files_list;
    parse_arguments(argc, argv, files_list);

    for (size_t i = 0; i < files_list.size(); ++i) {
        JackTokeniser token_machine(files_list[i].c_str());
        while (token_machine.hasMoreTokens()) {
            std::cout << "Token found : " << token_machine.getToken() << " - "
                      << static_cast<int>(token_machine.getTokenType()) << "\n";
            token_machine.showState();
            token_machine.advance();
        }

        std::cerr << "The rest is to be implemented by us \n";
    }

    return 0;
}

void parse_arguments(int argc, char** argv,
                     std::vector<std::string>& files_list) {
    // standard C++17 will use Boost::filesystem
    std::string argument;
    if (argc != 2) {
        std::cerr << "Print usage and exit because wrong number of arguments\n";
        exit(1);
        return;
    } else {
        argument = argv[1];
        std::cout << "Parsed argument : " << argument << "\n";
    }

    boost::filesystem::path p(argument);

    if (boost::filesystem::exists(p)) {
        if (boost::filesystem::is_regular_file(p)) {
            std::cerr << "Unique file mode\n";
            files_list.push_back(argument);
        } else if (boost::filesystem::is_directory(p)) {
            std::cerr << "Directory input detected but not implemented\n";
        }
    } else {
        std::cerr << p << " does not exist\n";
        exit(1);
    }

    return;
}
