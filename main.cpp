/*
    main.cpp
    Last update: 03/16/2025

    Document generator
    Take in data and create formatted text file
*/

#include "functions.h"

int main()
{

    /* Receive and process data */
    std::string order_number;
    std::string name;
    std::string address;
    std::string phone_number;
    std::string email_address;
    std::string tv_size;
    std::string tv_brand;
    std::string problem_description;

    get_work_order_number(order_number);
    get_name(name);
    get_address(address);
    get_phone_number(phone_number);
    get_email_address(email_address);
    get_tv_size(tv_size);
    get_tv_brand(tv_brand);
    get_problem_description(problem_description);

    std::string tv_summary = generate_tv_summary(tv_size, tv_brand, problem_description);

    // Change to struct
    std::string file_data[6] = {
        order_number,
        name,
        address,
        phone_number,
        email_address,
        tv_summary};

    /* Output data to text file */
    std::ofstream file;

    std::string filename = generate_filename(order_number, name);

    write_file(filename, file_data);

    return 0;
}