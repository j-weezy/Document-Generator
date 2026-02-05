/*
    ExtractorParser.cpp

    Last edit: 07/28/2025
        - format_phone_number()
            - Moved check for empty phone number to before size() < 4
*/

#include "ExtractorParser.h"

void ExtractorParser::parse_data(HTMLData::ExtractedData &data)
{
    trim_spaces(data);

    m_fdata.order_number = data.order_number;
    m_fdata.name = data.customer_name;
    m_fdata.address = data.customer_addr;

    std::string phone_number = parse_phone_number(data.customer_phone);
    phone_number = format_phone_number(phone_number);
    m_fdata.phone_number = phone_number;

    m_fdata.email_address = data.customer_email;
    m_fdata.tv_summary = get_tv_summary(data.tv_model, data.tv_manufacturer, data.tv_serial);
    m_fdata.problem_descr = data.problem_descr;
}

FileData ExtractorParser::get_data()
{
    return m_fdata;
}

std::string ExtractorParser::parse_phone_number(const std::string &input_number)
{
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
    std::string formatted_number = "";

    if (phone_number == "")
        phone_number = empty_number;

    if (phone_number.size() < 4)
        return phone_number;

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
    tv_summary += " TV - ";
    tv_summary += tv_serial;
    return tv_summary;
}

std::string ExtractorParser::get_size_from_model(std::string &tv_model)
{
    std::string tv_size = "";
    for (char c : tv_model)
    {
        if (!tv_size.empty())
        {
            if (!isdigit(c))
            {
                tv_size.clear();
            }
            else
            {   // Second digit - First two digit number found
                tv_size += c;
                break;
            }
        }
        else if (tv_size.empty() && isdigit(c))
        {
            tv_size += c;
        }
    }
    
    if (tv_size.empty())
    {
        std::cout << "TV size not found -> defaulted to 0" << std::endl;
        return "0";
    }
    else
    {
        return tv_size;
    }
}

void ExtractorParser::trim_spaces(HTMLData::ExtractedData &data)
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

const std::string ExtractorParser::empty_number = "0000000000";