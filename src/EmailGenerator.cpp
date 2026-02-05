/*
    EmailGenerator.cpp
*/

#include "EmailGenerator.h"

using namespace Email;

/*
Hello, I'm messaging to confirm the details of our phone conversation.
We've scheduled a service date of
Day mm/dd/yyyy @[time]

For a [size] [brand] TV at:


The service will take 1 - 1.5hrs. It will help me to have a clear surface to set the TV on its face.
*/
void EmailGenerator::generate_email_text(FileData &fdata)
{
    m_email_text += email_boilerplate.beginning;
    m_email_text += "\n";
    m_email_text += get_date_text(fdata.appointment_date);
    m_email_text += "\n\n";
    m_email_text += "For ";
    m_email_text += fdata.tv_summary;
    m_email_text += " at:\n";
    m_email_text += fdata.address;
    m_email_text += "\n\n";
    if (m_is_diagnostic)
        m_email_text += email_boilerplate.ending_diagnostic;
    else
        m_email_text += email_boilerplate.ending;
}

void EmailGenerator::set_diagnostic(bool is_diagnostic)
{
    m_is_diagnostic = is_diagnostic;
}

std::string EmailGenerator::get_email_text()
{
    return m_email_text;
}

// private:

std::string EmailGenerator::get_date_text(const std::string &date)
{
    if (date.empty())
        return "";
    if (!is_valid_date(date))
    {
        std::cout << "Bad date: " << date << " passed to EmailGenerator." << std::endl;
        return "";
    }
    std::string result = "";
    result += get_day_of_the_week(date);
    result += " ";
    result += date.substr(0, 5); // MM/DD
    result += " @";
    result += get_time_from_date(date);
    return result;
}

std::string EmailGenerator::get_day_of_the_week(const std::string &date)
{
    // Convert to std::tm format
    // {second, minute, hour, 1-based day, 0-based month, 
    //  year since 1900}
    // Date is in the form MM/DD/YYYY HH:MM
    int month = std::stoi(date.substr(0, 2)) - 1;
    int day = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));
    std::tm time_in = {0, 0, 0, day, month, year - 1900};
    std::time_t time_temp = std::mktime(&time_in);
    const std::tm *time_out = std::localtime(&time_temp);
    switch (time_out->tm_wday)
    {
    case 0:
        return "Sunday";
    case 1:
        return "Monday";
    case 2:
        return "Tuesday";
    case 3:
        return "Wednesday";
    case 4:
        return "Thursday";
    case 5:
        return "Friday";
    case 6:
        return "Saturday";
    default:
        std::cerr << "Bad appointment date. Cannot get week day." << std::endl;
        return "";
    }
}

std::string EmailGenerator::get_time_from_date(const std::string &date)
{   /* date is of the form "MM/DD/YYYY HH:MM" */
    std::string result = "";
    int hour_int = std::stoi(date.substr(11, 2));
    bool pm = hour_int > 11;
    if (hour_int > 12)
        hour_int -= 12;
    std::string minute_str = date.substr(14, 2);
    result += std::to_string(hour_int);
    if (minute_str != "00")
        result = result + ":" + minute_str;
    if (pm)
        result += "pm";
    else
        result += "am";
    return result;
}

/* 
date is of the form "MM/DD/YYYY HH:MM"
16 characters in length
This should be enforced by code that adds the data. The check
is necessary because data is loaded by load_json_data_from_file()
from an unprotected JSON file
*/
bool EmailGenerator::is_valid_date(const std::string &date)
{
    constexpr int MONTH_IDX = 0;
    constexpr int DAY_IDX = 3;
    constexpr int YEAR_IDX = 6;
    constexpr int HOUR_IDX = 11;
    constexpr int MINUTE_IDX = 14;

    int starting_idx = 0; // Points to month
    int matched_number = 0;

    // Validate form
    if (date.size() != 16)
        return false;
    if ((date[2] != '/') || (date[5] != '/'))
        return false;
    if (date[10] != ' ')
        return false;
    if (date[13] != ':')
        return false;
    // Valid form

    if ((!parse_date_number(date, MONTH_IDX, 2, matched_number)) || (matched_number < 1) || (matched_number > 12))
        return false;
    if ((!parse_date_number(date, DAY_IDX, 2, matched_number)) || (matched_number < 1) || (matched_number > 31))
        return false;
    if ((!parse_date_number(date, YEAR_IDX, 4, matched_number)) || (matched_number < 2000) || (matched_number > 2200))
        return false;
    if ((!parse_date_number(date, HOUR_IDX, 2, matched_number)) || (matched_number < 0) || (matched_number > 23))
        return false;
    if ((!parse_date_number(date, MINUTE_IDX, 2, matched_number)) || (matched_number < 0) || (matched_number > 59))
        return false;

    return true;
}

bool EmailGenerator::parse_date_number(const std::string &date, const int starting_idx, int length, int &output)
{
    output = 0;
    if (starting_idx + length > date.size())
        length = date.size() - starting_idx;
    for (int i = starting_idx; i < starting_idx + length; ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
        output = output * 10 + (date[i] - '0');
    }
    return true;
}