#include <boost/filesystem.hpp>  // Is included in std=c++17
#include <iostream>
#include <string>
#include <vector>

#include "grammar_engine/grammar_engine.h"
#include "tokeniser/tokeniser.h"

/* Parse the arguments of the executable
 * Side effect : fill files_list with the names of valid input names
 */
void parse_arguments(int argc, char** argv,
                     std::vector<std::string>& files_list);

int main(int argc, char** argv) {
    std::vector<std::string> files_list;
    parse_arguments(argc, argv, files_list);

    std::cerr << "We found " << files_list.size() << " files to compile.\n";

    /* Loop over all the parsed filenames */
    for (size_t i = 0; i < files_list.size(); ++i) {
        std::string output_filename = files_list[i];
        output_filename.replace(output_filename.end() - 4,
                                output_filename.end(), "xml");

        std::cerr << "Converting " << files_list[i] << " into "
                  << output_filename << "\n";
        JackGrammarEngine* file_compiler = new JackGrammarEngine(files_list[i]);

        file_compiler->start();

        // TODO : Change this once the debugging phase is over
        /* JackTokeniser* token_machine = file_compiler->getTokeniser(); */
        /* while (token_machine->hasMoreTokens()) { */
        /*     std::cout << "Token found : " << token_machine->getToken() << " -
         * " */
        /*               << static_cast<int>(token_machine->getTokenType()) */
        /*               << "\n"; */
        /*     token_machine->showState(); */
        /*     token_machine->advance(); */
        /* } */

        std::cout << "Done !\n";
        delete file_compiler;
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
            std::cerr << p.generic_string() << "is a folder containing :\n";
            boost::filesystem::directory_iterator dir_iter(p);
            typedef std::vector<boost::filesystem::path> vec;
            vec p_dir_listing;  // so we can sort thelater

            copy(boost::filesystem::directory_iterator(p),
                 boost::filesystem::directory_iterator(),
                 back_inserter(p_dir_listing));
            auto it = p_dir_listing.begin();
            while (it != p_dir_listing.end()) {
                std::string filename = it->generic_string();
                std::cerr << filename << "\n";
                if (it->extension() == ".jack") {
                    files_list.push_back(filename);
                }
                ++it;
            }
        }
    } else {
        std::cerr << p << " does not exist\n";
        exit(1);
    }

    return;
}
