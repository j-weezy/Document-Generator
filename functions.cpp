/*
    functions.cpp
    Last update: 03/16/2025 - Added remove_trailing_and_leading_spaces() function

    Definition of functions for Document Generator
*/

#include "functions.h"

/* Getters */

void get_work_order_number(std::string &order_number)
{
    do
    {
        // Prompt user for work order number
        std::cout << "Enter Work Order Number: ";
        std::cin >> order_number;
    } while (!valid_order_number(order_number));

    std::cout << "Registered Work Order Number: " << order_number << std::endl;
    std::cout << std::endl; // Vertical padding
}

void get_name(std::string &name)
{
    // Prompt user for end user name
    while (true)
    {
        std::string edit = ""; // Used to re-enter name
        std::string first_name;
        std::string last_name;
        std::string flush_str;

        std::cout << "Enter End User name: ";
        std::cin >> first_name >> last_name;
        name = first_name + " " + last_name;

        std::string reg_name = parse_name(name);
        std::cout << "Registered name: " << reg_name << std::endl;

        std::cout << "Type \"e\" to re-enter or press enter to continue: ";

        clear_input_buffer_spaces(); // Clear std::cin buffer

        getline(std::cin, edit);
        if (edit != "e")
        {
            name = reg_name;
            break;
        }
    }
    std::cout << std::endl; // Vertical padding
}

void get_address(std::string &address)
{
    // Prompt user for address
    /*
        Broken into three parts:
            Street Address
            City
            Zip code
        This is to reduce some of the complexity of validating the data
    */
    // Get street address
    while (true)
    {
        std::string street_address;
        std::string edit = "";

        std::cout << "Enter street address: " << std::endl;
        getline(std::cin, street_address);
        remove_trailing_and_leading_spaces(street_address);

        std::cout << "Registered street address: " << std::endl;
        std::cout << street_address << std::endl;
        std::cout << "Type \"e\" to re-enter or press enter to continue: ";

        getline(std::cin, edit);
        if (edit == "e")
        {
            continue;
        }
        else
        {
            address = street_address;
            break;
        }
    }
    std::cout << std::endl; // Vertical padding

    // Now get city
    while (true)
    {
        std::string city;
        std::string edit = "";

        std::cout << "Enter city: ";
        std::cin >> city;

        std::cout << "Registered city: " << city << std::endl;
        std::cout << "Type \"e\" to re-enter or press enter to continue: ";

        clear_input_buffer_spaces();
        getline(std::cin, edit);
        if (edit == "e")
        {
            continue;
        }
        else
        {
            address += '\n' + city + ", WA ";
            break;
        }
    }

    // Get zip code
    std::string zip;
    do
    {
        std::cout << "Enter zip code: ";
        std::cin >> zip;
        clear_input_buffer_spaces(); // Flush cin
    } while (!valid_zip_code(zip));
    std::cout << "Registered zip code: " << zip << std::endl;
    address += zip;

    std::cout << "Registered address:" << std::endl;
    std::cout << address << std::endl;
    std::cout << std::endl; // Vertical padding
}

void get_phone_number(std::string &phone_number)
{
    while (true)
    {
        std::string edit;
        // Prompt user for phone number
        std::cout << "Enter end user phone number: ";
        getline(std::cin, phone_number);
        phone_number = parse_phone_number(phone_number);
        phone_number = format_phone_number(phone_number);

        std::cout << "Registered phone number: " << phone_number << std::endl;
        std::cout << "Type \"e\" to re-enter or press enter to continue: ";

        getline(std::cin, edit);
        if (edit == "e")
        {
            phone_number = "";
            continue;
        }
        else
        {
            break;
        }
    }
    std::cout << std::endl; // Vertical padding
}

void get_email_address(std::string &email_address)
{
    do
    {
        email_address = ""; // Reset email_address container

        // Prompt for End User email address
        std::cout << "Enter end user email adddress: ";
        std::cin >> email_address;

    } while (!valid_email_address(email_address));

    std::cout << "Registered email address: " << email_address << std::endl;
    std::cout << std::endl; // Vertical padding
}

void get_tv_size(std::string &tv_size)
{
    do
    {
        tv_size = ""; // Reset tv_size container

        // Prompt user for TV size
        std::cout << "Enter TV size in inches: ";
        std::cin >> tv_size;

    } while (!valid_tv_size(tv_size));
    std::cout << std::endl; // Vertical padding
}

void get_tv_brand(std::string &tv_brand)
{
    while (true)
    {
        tv_brand = ""; // Reset brand container
        std::string edit;   // Used to re-enter brand

        // Prompt user for TV brand
        std::cout << "Enter TV brand: ";
        clear_input_buffer_spaces();
        getline(std::cin, tv_brand);

        std::cout << "Registered brand: " << tv_brand << std::endl;

        std::cout << "Type \"e\" to re-enter or press enter to continue: ";

        getline(std::cin, edit); // getline used to flush cin
        if (edit == "e")
        {
            continue;
        }
        else
        {
            break;
        }
    }
    std::cout << std::endl; // Vertical padding
}

void get_problem_description(std::string &problem_description)
{
    // Prompt for problem description
    std::cout << "Enter problem description: " << std::endl;
    getline(std::cin, problem_description);
    std::cout << std::endl; // Vertical padding
}
// End getters

/* Validators */

bool valid_order_number(std::string order_number)
{
    if (order_number.size() != 10)
    {
        return false;
    } // Correct size

    if (order_number.substr(0, 3) != "ITI")
    {
        return false;
    } // Starts with ITI

    for (int i = 3; i < order_number.size(); i++)
    {
        if (!isdigit(order_number.at(i)))
        {
            return false;
        }
    } // Remaining characters are digits

    return true;
}

bool valid_zip_code(std::string input_zip)
{
    if (input_zip.size() != 5)
    {
        return false;
    } // Correct size

    for (char c : input_zip)
    {
        if (!isdigit(c))
        {
            return false;
        }
    } // All digits

    return true;
}

bool valid_phone_number(std::string phone_number)
{
    if (phone_number.size() != 10)
    {
        return false;
    } // Correct size

    for (char c : phone_number)
    {
        if (!isdigit(c))
        {
            return false;
        }
    } // All digits

    return true;
}

bool valid_email_address(std::string email_address)
{
    // Valid email address is of the form a@b.c
    // This means minimum size is 5
    if (email_address.size() < 5)
    {
        return false;
    }

    int at_symbol_index = find_index(email_address, "@");
    if (at_symbol_index < 0)
    {
        // No @ symbol found
        return false;
    }
    if (email_address.find('@', at_symbol_index + 1) != std::string::npos)
    {
        // More than one @ symbol found
        return false;
    }
    int web_dot_index = find_index(email_address, ".", at_symbol_index);
    if (web_dot_index < 0)
    {
        // No period after @ symbol found
        return false;
    }
    if (email_address.find('.', web_dot_index + 1) != std::string::npos)
    {
        // More than one period after @ symbol found
        return false;
    }

    return true;
}

bool valid_tv_size(std::string tv_size)
{
    // TV sizes are two digit integers
    if (tv_size.size() != 2)
    {
        return false;
    }

    for (char c : tv_size)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}
// End validators

/* String manipulators */
std::string parse_name(std::string input_name)
{
    std::string first_name = "";
    std::string last_name = "";

    // Check for space
    if (input_name.find(" ") < input_name.size())
    {
        first_name = input_name.substr(0, input_name.find(" "));
        last_name = input_name.substr(input_name.find(" ") + 1, input_name.size() - 1);
    }
    else
    {
        first_name = input_name;
    }

    return first_name + " " + last_name;
}

std::string parse_phone_number(std::string input_number)
{
    std::cout << "Parsing phone number..." << std::endl;
    const std::string empty_number = "0000000000"; // Return for invalid inputs
    std::string parsed_number = "";

    if (input_number == "")
    {
        return empty_number;
    }

    for (char c : input_number)
    {
        if (isdigit(c))
        {
            parsed_number += c;
        }
    }
    if (parsed_number == "")
    {
        return empty_number;
    }

    return parsed_number;
}

std::string format_phone_number(std::string phone_number)
{
    std::cout << "Formatting phone number: " << phone_number << "..." << std::endl;
    const std::string empty_number = "0000000000";
    std::string formatted_number = "";

    if (phone_number.size() < 4)
    {
        return phone_number;
    } // Needs to be at least 4 characters

    if (phone_number == "")
    {
        phone_number = empty_number;
    }

    for (int i = 0; i < phone_number.size(); i++)
    {
        char digit = phone_number.at(phone_number.size() - 1 - i);
        std::string s_digit{digit}; // Cast to std::string for concatenation
        formatted_number = s_digit + formatted_number;
        switch (i)
        {
        case 3:
            formatted_number = "-" + formatted_number;
            break;
        case 6:
            formatted_number = ")-" + formatted_number;
            break;
        case 9:
            formatted_number = "(" + formatted_number;
            break;
        }
    }

    return formatted_number;
}

std::string generate_tv_summary(std::string tv_size, std::string tv_brand, std::string problem_description)
{
    std::string tv_summary = ""; // [TV size]" [TV brand] TV - [problem description]

    tv_summary += tv_size + "\" ";
    tv_summary += tv_brand + " TV - ";
    tv_summary += problem_description;

    return tv_summary;
}

std::string generate_filename(std::string order_number, std::string name)
{
    std::string filename = "";

    filename += order_number;
    filename += " - ";
    filename += name;
    filename += ".txt";

    return filename;
}
// End std::string manipulators

/* File writer */
void write_file(
    const std::string filename,
    const std::string order_number,
    const std::string name,
    const std::string address,
    const std::string phone_number,
    const std::string email_address,
    const std::string tv_summary)
{
    std::ofstream file;

    // Create file
    file.open(filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    // Add work order number to the top of the document
    file << order_number << std::endl;
    file << std::endl; // Vertical padding

    file << "Name: " << name << std::endl;
    file << std::endl; // Vertical padding

    file << "Address:" << std::endl;
    file << address << std::endl;
    file << std::endl; // Vertical padding

    file << "Phone: " << phone_number << std::endl;
    file << std::endl;

    file << "Email: " << email_address << std::endl;
    file << std::endl;

    file << tv_summary;

    file.close();
}

void write_file(const std::string filename, std::string data[6])
{
    std::ofstream file;

    std::string foldername = filename;
    foldername.erase(foldername.size() - 4, 4); // Remove .txt

    std::filesystem::create_directories("./" + foldername);

    file.open(foldername + "/" + filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    // Add work order number to the top of the document
    file << data[0] << std::endl;
    file << std::endl; // Vertical padding

    file << "Name: " << data[1] << std::endl;
    file << std::endl;

    file << "Address:" << std::endl;
    file << data[2] << std::endl;
    file << std::endl;

    file << "Phone: " << data[3] << std::endl;
    file << std::endl;

    file << "Email: " << data[4] << std::endl;
    file << std::endl;

    file << data[5];

    file.close();
}
// End file writers

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