/*
    main.cpp

    Run Document Generator with user input.
    The Document Generator creates documents to help with managing info
    related to TV repair work orders.
*/

#include "DocGen.h"
#include <iostream>

int main(int argc, char **argv)
{
    DocGen doc_gen;
    const std::string HTML_DOC_TITLE = "ITI - Order Status Details.html";
    std::cout << std::endl; // Vertical buffer for readable output
    if (argc > 1)
        doc_gen.write_file(HTML_DOC_TITLE.c_str(), *argv[1]);
    else
        doc_gen.write_file(HTML_DOC_TITLE.c_str());

    return 0;
}