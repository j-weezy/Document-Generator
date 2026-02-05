/*
    EmailGenerator.h

    Should change logic to use only FileData and not JSON
*/

#pragma once

#include "filedata.h"
#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

using json = nlohmann::json;

namespace Email
{
    struct EmailBoilerplate
    {
        std::string beginning = "Hello, I'm messaging to confirm the details of our phone conversation.\nWe've scheduled a service date of";
        std::string ending = "The service will take 1 - 1.5hrs. It will help me to have a clear surface to set the TV on its face.";
        std::string ending_diagnostic;
    };

    inline EmailBoilerplate email_boilerplate;
    
    class EmailGenerator
    {
    public:
        void generate_email_text(FileData &fdata);
        void set_diagnostic(bool is_diagnostic);
        std::string get_email_text();

        /* Exposed for use in DocGen */
        bool is_valid_date(const std::string &date);

    private:
        // json m_jdata;
        std::string m_email_filename;
        std::string m_email_text = "";
        bool m_is_diagnostic = false;
        
        std::string get_date_text(const std::string &date);
        std::string get_day_of_the_week(const std::string &date);
        std::string get_time_from_date(const std::string &date);

        /*
        Parses substring from string of form "MM/DD/YYYY HH:MM"
        By setting starting_idx and length, individual numbers can be
        parsed from the date.
        Returns true if parsing was successful, i.e. the characters
        parsed were all digits.
        Returns false if parsing was unsuccessful, i.e. at least one
        parsed character was not a digit.
        The resulting number is stored in output.
        */
        bool parse_date_number(const std::string &date, const int starting_idx, int length, int &output);
    };
}