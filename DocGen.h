/*
    DocGen.h
    Last updated: 07/25/2025
*/

#ifndef DOCGEN_H
#define DOCGEN_H

#include <fstream>
#include <filesystem>
#include "HTMLDataExtractor.h"
#include "filedata.h"
#include "ExtractorParser.h"

class DocGen
{   
public:
    void gen_data(const char *filename);
    void write_file();
    
private:
    FileData fd;

    std::string gen_foldername();
    std::string gen_filename(); // Helper for write_file
};

#endif