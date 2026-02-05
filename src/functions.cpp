/*
    functions.cpp
    Last update: 02/03/2026

    Definition of functions for Document Generator
*/

#include "functions.h"

namespace fs = std::filesystem;

/* Helper functions */
void remove_trailing_and_leading_spaces(std::string &target_str)
{
    while (!isalpha(target_str.front()) && !isdigit(target_str.front()))
    {
        target_str.erase(0, 1);
    }

    while (!isalpha(target_str.back()) && !isdigit(target_str.back()))
    {
        target_str.erase(target_str.size() - 1, 1);
    }
}

std::vector<std::string> get_files_in_current_directory()
{
    std::vector<std::string> files;
    fs::path current_dir = ".";

    try
    {
        for (const auto &entry : fs::directory_iterator(current_dir))
        {
            if (fs::is_regular_file(entry.status()))
                files.push_back(entry.path().filename().string());
        }
    }
    catch (const fs::filesystem_error &e){
        std::cerr << "Filesystem error: " << e.what() << std::endl;}
    
    return files;
}
// End helper functions