/*
    functions.h
    Last update: 07/26/2025

    Declaration of functions for Document Generator
*/

#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

void remove_trailing_and_leading_spaces(std::string &target_str);
std::vector<std::string> get_files_in_current_directory();