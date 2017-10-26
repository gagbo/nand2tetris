/* Copyright 2017 Gerry Agbobada
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <boost/filesystem.hpp>  // Is included in std=c++17
#include <iostream>
#include <string>
#include <vector>

#include "compilation_engine/compilation_engine.h"
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

        std::cerr << "Converting " << files_list[i] << "\n";
        JackCompilationEngine* file_compiler =
            new JackCompilationEngine(files_list[i]);

        file_compiler->start();

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
