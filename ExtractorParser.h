/*
    ExtractorParser.h
*/

#ifndef EXTRACTORPARSER_H
#define EXTRACTORPARSER_H

#include "HTMLDataExtractor.h"
#include "filedata.h"

class ExtractorParser
{
public:
    void parse_data(HTMLDataExtractor &extractor);
    FileData get_data();
private:
    FileData fd;
    void trim_spaces(ExtractedData &data);
    std::string parse_phone_number(std::string &input_number);
    std::string format_phone_number(std::string phone_number);
    std::string get_tv_summary(std::string &tv_model, std::string &tv_manufacturer, std::string &tv_serial);
    std::string get_size_from_model(std::string &tv_model);
};

#endif