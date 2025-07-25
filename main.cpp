/*
    main.cpp
    Last update: 07/25/2025

    Document generator
    Take in data and create formatted text file

    To use, download work order webpage and save ITI - Order Status Details.html
    in the same directory as the executable
*/

#include "DocGen.h"

int main()
{
    const char *filename = "ITI - Order Status Details.html"; // Filename from saved webpage
    DocGen doc;
    doc.gen_data(filename);
    doc.write_file();

    return 0;
}