/*
    functions.cpp
    Last update: 07/16/2025

    Definition of functions for Document Generator
*/

#include "functions.h"

/* Helper functions */

void clear_input_buffer_spaces()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void remove_all_spaces(std::string &target_str)
{
    auto it = remove(target_str.begin(), target_str.end(), ' ');
    target_str.erase(it, target_str.end());
}

int find_index(const std::string &target_string, const std::string &sub_str, int start_index)
{
    size_t index = target_string.find(sub_str, start_index);
    if (index == std::string::npos)
    {
        // Sub std::string not found
        return -1;
    }

    return static_cast<int>(index);
}

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
// End helper functions