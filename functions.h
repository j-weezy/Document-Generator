/*
    functions.h
    Last update: 03/16/2025

    Declaration of functions for Document Generator
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <limits>

// Getters
void get_work_order_number(std::string &order_number);
void get_name(std::string &name);
void get_address(std::string &address);
void get_phone_number(std::string &phone_number);
void get_email_address(std::string &email_address);
void get_tv_size(std::string &tv_size);
void get_tv_brand(std::string &tv_brand);
void get_problem_description(std::string &problem_description);

// Validators
bool valid_order_number(std::string order_number); // Valid order numbers are ten character strings of the form ITI#######
bool valid_zip_code(std::string input_zip); // Valid zip codes are five digits
bool valid_phone_number(std::string phone_number);
bool valid_email_address(std::string email_address);
bool valid_tv_size(std::string tv_size);

// String manipulators
std::string parse_name(std::string input_name);
std::string parse_phone_number(std::string input_number);
std::string format_phone_number(std::string phone_number);
std::string generate_tv_summary(std::string tv_size, std::string tv_brand, std::string problem_description);
std::string generate_filename(std::string order_number, std::string name);

// File writer
void write_file(
    const std::string filename,
    const std::string order_number,
    const std::string name,
    const std::string address,
    const std::string phone_number,
    const std::string email_address,
    const std::string tv_summary);

/*
    write_file overload
    *This version is easier to read when called*

    Create output file
    Data is passed as an array for readability.
    The array must be size 6 and have the structure:
        {order number, name, address, phone number, email address, tv summary}
*/
void write_file(const std::string filename, std::string data[6]);

// Helper functions
int find_index(const std::string &target_string, const std::string &sub_str, int start_index = 0);
void remove_all_spaces(std::string &target_str);
void clear_input_buffer_spaces(); // Call this before using getline after a cin call
void remove_trailing_and_leading_spaces(std::string &target_str);

#endif