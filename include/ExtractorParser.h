/*
    ExtractorParser.h

    The ExtractorParser uses an HTMLData::Extractor object to get raw
    data from HTML and format the data into readable strings in a 
    FileData struct.
*/

#pragma once

#include "HTMLDataExtractor.h"
#include "functions.h"
#include "filedata.h"

class ExtractorParser
{
public:
    /*
    Calls get_data() on the HTMLData::Extractor object to get raw
    data and call member functions to format the data which is 
    stored as a FileData class member which can be copied by 
    calling get_data().
    */
    void parse_data(HTMLData::ExtractedData &data);
    FileData get_data();

private:
    FileData m_fdata;

    /*
    Call remove_trailing_and_leading_spaces() on each member of FileData
    */
    void trim_spaces(HTMLData::ExtractedData &data);

    /*
    Extract digits from raw phone number data.
    */
    std::string parse_phone_number(const std::string &input_number);

    /*
    Format phone number into (###)-###-####.
    If phone number is empty, the result will be (000)-000-0000.
    If the phone number is less than 4 digits, it is returned.
    */
    std::string format_phone_number(std::string phone_number);

    /*
    Combine and format raw TV description data.
    */
    std::string get_tv_summary(std::string &tv_model, std::string &tv_manufacturer, std::string &tv_serial);

    /*
    The first two consecutive digits of the TV model name represent the
    screen size in inches.
    Called by get_tv_summary()
    */
    std::string get_size_from_model(std::string &tv_model);
    static const std::string empty_number; // 0000000000
};