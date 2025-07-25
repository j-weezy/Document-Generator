/*
    ExtractorParser.cpp
*/

#include "ExtractorParser.h"

void ExtractorParser::parse_data(HTMLDataExtractor &extractor)
{
    ExtractedData data = extractor.get_data();
    trim_spaces(data);
    fd.order_number = data.order_number;
    fd.name = data.customer_name;
    fd.address = data.customer_addr;
    std::string phone_number = parse_phone_number(data.customer_phone);
    phone_number = format_phone_number(phone_number);
    fd.phone_number = phone_number;
    fd.email_address = data.customer_email;
    fd.tv_summary = get_tv_summary(data.tv_model, data.tv_manufacturer, data.tv_serial);
    fd.problem_descr = data.problem_descr;
}

FileData ExtractorParser::get_data()
{
    return fd;
}

std::string ExtractorParser::parse_phone_number(std::string &input_number)
{
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

std::string ExtractorParser::format_phone_number(std::string phone_number)
{
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

std::string ExtractorParser::get_tv_summary(std::string &tv_model, std::string &tv_manufacturer, std::string &tv_serial)
{
    // [TV size]" [TV brand] TV: [TV serial #]
    std::string tv_summary = get_size_from_model(tv_model);
    tv_summary += "\" ";
    tv_summary += tv_manufacturer;
    tv_summary += " TV: ";
    tv_summary += tv_serial;
    return tv_summary;
}

std::string ExtractorParser::get_size_from_model(std::string &tv_model)
{
    std::string tv_size = "";
    int count = 0; // Get first two digits in model #
    for (char c : tv_model)
    {
        if (isdigit(c))
        {
            tv_size += c;
            count++;
        }
        if (count == 2)
        {
            break;
        }
    }
    if (tv_size == "")
    {
        return "0";
    }
    return tv_size;
}

void ExtractorParser::trim_spaces(ExtractedData &data)
{
    remove_trailing_and_leading_spaces(data.order_number);
    remove_trailing_and_leading_spaces(data.customer_name);
    remove_trailing_and_leading_spaces(data.customer_addr);
    remove_trailing_and_leading_spaces(data.customer_phone);
    remove_trailing_and_leading_spaces(data.customer_email);
    remove_trailing_and_leading_spaces(data.tv_manufacturer);
    remove_trailing_and_leading_spaces(data.tv_model);
    remove_trailing_and_leading_spaces(data.tv_serial);
    remove_trailing_and_leading_spaces(data.problem_descr);
}