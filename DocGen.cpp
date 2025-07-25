/*
    DocGen.cpp
    Last updated 07/25/2025
*/

#include "DocGen.h"

void DocGen::gen_data(const char *filename)
{
    HTMLDataExtractor extractor;
    extractor.set_info(filename);
    ExtractorParser parser;
    parser.parse_data(extractor);
    fd = parser.get_data();
}

void DocGen::write_file()
{
    std::ofstream file;

    std::string foldername = gen_foldername();
    std::string filename = gen_filename();

    std::filesystem::create_directories("./" + foldername);

    file.open(foldername + "/" + filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    file << fd.order_number << std::endl;
    file << std::endl;

    file << "Name: " << fd.name << std::endl;
    file << std::endl;

    file << "Address:" << std::endl;
    file << fd.address << std::endl;
    file << std::endl;

    file << "Phone: " << fd.phone_number << std::endl;
    file << std::endl;

    file << "Email: " << fd.email_address << std::endl;
    file << std::endl;

    file << fd.tv_summary << std::endl;
    file << std::endl;

    file << fd.problem_descr;

    file.close();
}

std::string DocGen::gen_foldername()
{
    std::string foldername = fd.order_number;
    foldername += " - ";
    foldername += fd.name;

    return foldername;
}

std::string DocGen::gen_filename()
{
    std::string filename = fd.order_number;
    filename += " - ";
    filename += fd.name;
    filename += ".txt";

    return filename;
}