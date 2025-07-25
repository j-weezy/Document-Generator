/*
    filedata.h

    Declare FileData struct type
*/

#ifndef FILEDATA_H
#define FILEDATA_H

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
};

#endif