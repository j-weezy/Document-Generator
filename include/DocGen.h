/*
    DocGen.h
    Last updated: 02/03/2026

        To use the DocGen, place the target HTML file in the current
    directory. The name of the target HTML file is hardcoded at the
    moment. Call gen_data() to populate the data for the first
    write. Then call write_file() to create the work order (wo) notes
    text file and generate an email. The function of write_file()
    can be changed by passing a single char.

        The default behavior is to create the wo notes text file, this
    is also true for the inputs 'w' and 'W'.

        To set an appointment date, pass 's' or 'S' to write_file().

        To write a templated email to the wo notes text file, pass 'e'
    or 'E' to write_file(). This will create a wo notes file if
    one has not yet been created.

    The Document Generator should be available globally, i.e. the exe
    should be able to be run from any directory. This is because the
    secondary functions, e.g. email generation and appointment setting,
    must be done in the directory created by the primary function
    write_wo_notes_file()
*/

#pragma once


#include "HTMLDataExtractor.h"
#include "filedata.h"
#include "ExtractorParser.h"
#include "EmailGenerator.h"
#include "functions.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>
#include <vector>

using json = nlohmann::json;

class DocGen
{
public:
    void write_file(const char *filename, char opt = 'w');

private:
    FileData m_fdata;
    json m_jdata;
    HTMLData::Extractor m_extractor;
    ExtractorParser m_parser;
    Email::EmailGenerator m_email_generator;

    /* These are both set at once by set_filenames() */
    std::string m_wo_filename;
    std::string m_json_filename;

    static const std::string file_text_separator;

    /*
    Get parsed data from HTMLData::Extractor object.
    Returns boolean to indicate whether data was generated successfully.
    */
    bool gen_data(const char *filename);

    /*
    This is the primary function of the Document Generator. It must be
    run in the same directory as the HTML file containing the WO.
    Creates a directory for the WO info. The "WO Notes File," the JSON
    file, and the Photos subdirectory. The "WO Notes File" contains the
    useful data from the WO HTML file in a more readable format.
    */
    bool write_wo_notes_file();

    /*
    This needs to be called in the directory created by
    write_wo_notes_file().
    */
    bool write_email_to_notes_file();

    /*
    Generate initial folder name:
        [WO Number] - [EU Name]
    */
    std::string gen_foldername();

    /*
    Generate .txt and .json file names from FileData.
    Called with no argument will return .txt file name.
    */
    std::string gen_filename(bool gen_json = false);

    void save_json_to_file(std::string parent_dir="");
    json filedata_to_json(FileData &fdata);
    void load_json_from_file();
    FileData json_to_filedata(json &jdata);

    /*
    Call this in the WO directory. Uses directory context to find file
    names for WO notes file and JSON file.
    Returns boolean indicating whether it was successful.
    */
    bool set_filenames();
    bool is_valid_wo_file(const std::string &filename);
    std::string get_json_filename();

    /*
    Right now set_apointment_date() ("sad()") is only called with the 
    return from get_appointment_date_from_input() as an input. I've 
    considered changing sad() so it calls gadfi() itself and accepts
    no input.
    For now, I think I've decided it makes the function calls a little
    bit more understandable. That is, it's clear in the calls that the
    appointment date is being set and that it's coming from user input.
    */
    void set_appointment_date(const std::string &date);
    std::string get_appointment_date_from_input();

    void print_help_message();
};