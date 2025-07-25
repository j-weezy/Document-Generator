/*
    HTML_Data.h

    Declaration of HTMLDataExtractor class
    Intended to extract data from HTML file. The data is considered
    raw because there is no processing done by the data extractor
*/

#ifndef HTMLDATAEXTRACTOR_H
#define HTMLDATAEXTRACTOR_H

#include <iostream>
#include <string>
#include <libxml2/libxml/HTMLparser.h>
#include <libxml2/libxml/xpath.h>
#include "functions.h"

struct ExtractedData
{
    std::string order_number;
    std::string customer_name;
    std::string customer_addr;
    std::string customer_phone;
    std::string customer_email;
    std::string tv_manufacturer;
    std::string tv_model;
    std::string tv_serial;
    std::string problem_descr;   
};

class HTMLDataExtractor
{
public:
    void set_info(const char *filename);
    ExtractedData get_data();
    
private:
    ExtractedData data;

    std::string get_order_id_number(xmlXPathContextPtr ctx);

    /*
        Valid label_text values are:
            Name
            Address
            Phone No
            Alt Phone
            Fax No
            Email
        DOES NOT VALIDATE
    */
    std::string get_customer_contact_field(xmlXPathContextPtr ctx, const std::string &label_text);
    std::string get_customer_addr(xmlXPathContextPtr ctx);

    /*
        Valid label_text values are:
            Manufacturer
            Model#
            Serial#
        DOES NOT VALIDATE
    */
    std::string get_product_information_field(xmlXPathContextPtr ctx, const std::string &label_text);
    std::string get_problem_description(xmlXPathContextPtr ctx);
};

#endif