/*
    functions.h
    Last update: 07/16/2025

    Declaration of functions for Document Generator
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

// Helper functions
int find_index(const std::string &target_string, const std::string &sub_str, int start_index = 0);
void remove_all_spaces(std::string &target_str);
void clear_input_buffer_spaces(); // Call this before using getline after a cin call
void remove_trailing_and_leading_spaces(std::string &target_str);

#endif