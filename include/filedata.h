/*
    filedata.h

    Declare FileData struct type

    FileData contains data ready to be input into file.
*/

#pragma once

#include <string>

struct FileData
{
    std::string order_number;
    std::string name;
    std::string address;
    std::string phone_number;
    std::string email_address;
    std::string tv_summary;
    std::string problem_descr;
    std::string appointment_date;
};