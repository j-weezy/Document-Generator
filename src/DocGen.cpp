/*
    DocGen.cpp
    Last updated 02/03/2026
*/

#include "DocGen.h"

const std::string DocGen::file_text_separator =
    "+----------------------------------------------------------------+\n\n";

void DocGen::write_file(const char *filename, char opt)
{
    switch (opt)
    {
    case 'w':
    case 'W':
    default:
        if (!gen_data(filename))
        {
            std::cout << "Data generation unsuccessful.\n";
            std::cout << "Exiting..." << std::endl;
            break;
        }
        if (!write_wo_notes_file())
        {
            std::cout << "Write WO Notes file unsuccessful\n";
            std::cout << "Exiting..." << std::endl;
        }
        break;
    case 'e':
    case 'E':
        if (!set_filenames())
        {
            std::cout << "Set filenames unsuccessful.\n";
            std::cout << "Exiting..." << std::endl;
            break;
        }
        // Create wo notes file if not created
        // Set appointment date if not set
        if (m_fdata.appointment_date.empty())
            set_appointment_date(get_appointment_date_from_input());
        // Generate email
        if (!write_email_to_notes_file())
        {
            std::cout << "Write email to notes file unsuccessful.\n";
            std::cout << "Exiting..." << std::endl;
        }
        break;
    case 's':
    case 'S':
        if (!set_filenames())
        {
            std::cout << "Set filenames unsuccessful.\n";
            std::cout << "Exiting..." << std::endl;
            break;
        }
        set_appointment_date(get_appointment_date_from_input());
        break;
    case 'h':
    case 'H':
        print_help_message();
        break;
    }
}

bool DocGen::gen_data(const char *filename)
{
    if (!m_extractor.set_info(filename))
    {
        std::cout << "Unable to generate data." << std::endl;
        return false;
    }
    // Temporary value used to store ExtractedData object.
    // This is necessary to check success of extraction before
    // passing data to parser.
    HTMLData::ExtractedData temp = m_extractor.get_info();
    m_parser.parse_data(temp);
    m_fdata = m_parser.get_data();
    m_jdata = filedata_to_json(m_fdata);

    return true;
}

/*
"[Order Number] - [EU Name].txt"

[Order Number]

Name: [EU Name]

Address:
[Address]

Phone: [EU Phone]

Email: [EU Email]

[TV Summary]

[Problem Description]
*/
bool DocGen::write_wo_notes_file()
{
    std::ofstream file;

    std::string foldername = gen_foldername();
    std::string filename = gen_filename();

    std::filesystem::create_directories("./" + foldername);
    std::cout << "Directory: /\"" << foldername << "\" created...\n";
    std::cout << std::endl;
    std::filesystem::create_directories(foldername + "/Photos");

    file.open(foldername + "/" + filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        return false;
    }

    file << m_fdata.order_number << "\n\n";

    file << "Name: " << m_fdata.name << "\n\n";

    file << "Address:" << '\n';
    file << m_fdata.address << "\n\n";

    file << "Phone: " << m_fdata.phone_number << "\n\n";

    file << "Email: " << m_fdata.email_address << "\n\n";

    file << m_fdata.tv_summary << "\n\n";

    file << m_fdata.problem_descr;
    file << std::flush;

    file.close();

    save_json_to_file(foldername);

    // Print success message
    std::cout << "WO notes successfully generated...\n"
              << std::endl;
    return true;
}

bool DocGen::write_email_to_notes_file()
{
    if (m_json_filename.empty() || m_wo_filename.empty())
        set_filenames();
    load_json_from_file();
    m_email_generator.generate_email_text(m_fdata);
    std::ofstream file;
    file.open(m_wo_filename, std::ios_base::app);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << m_wo_filename;
        std::cout << std::endl;
        return false;
    }
    file << "\n\n\n";
    file << file_text_separator;
    // Write email subject line
    file << "TV Service Confirmation: " << m_fdata.order_number;
    file << "\n\n";
    file << m_email_generator.get_email_text();
    file << std::flush;
    file.close();

    std::cout << "Email written to WO notes file." << std::endl;
    return true;
}

std::string DocGen::gen_foldername()
{
    std::string foldername = m_fdata.order_number;
    foldername += " - ";
    foldername += m_fdata.name;

    return foldername;
}

std::string DocGen::gen_filename(bool gen_json)
{
    std::string filename = m_fdata.order_number;
    filename += " - ";
    filename += m_fdata.name;
    if (gen_json)
        filename += ".json";
    else
        filename += ".txt";

    return filename;
}

void DocGen::save_json_to_file(std::string parent_dir)
{
    std::string filename = gen_filename(true);
    if (!parent_dir.empty())
        filename = parent_dir + "/" + filename;
    std::ofstream file;
    file.open(filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        exit(1);
    }
    file << m_jdata.dump() << std::flush;
    file.close();
}

/* 02/01/2026
struct FileData
{
    std::string order_number;
    std::string name;
    std::string address;
    std::string phone_number;
    std::string email_address;
    std::string tv_summary;
    std::string problem_descr;
    std::string appointment_date;
};
*/
json DocGen::filedata_to_json(FileData &fdata)
{
    json result =
        {
            {"order number", m_fdata.order_number},
            {"name", m_fdata.name},
            {"address", m_fdata.address},
            {"phone number", m_fdata.phone_number},
            {"email address", m_fdata.email_address},
            {"tv summary", m_fdata.tv_summary},
            {"problem description", m_fdata.problem_descr},
            {"appointment date", m_fdata.appointment_date}};
    return result;
}

FileData DocGen::json_to_filedata(json &jdata)
{
    FileData result;
    result.order_number = jdata["order number"];
    result.name = jdata["name"];
    result.address = jdata["address"];
    result.phone_number = jdata["phone number"];
    result.email_address = jdata["email address"];
    result.tv_summary = jdata["tv summary"];
    result.problem_descr = jdata["problem description"];
    result.appointment_date = jdata["appointment date"];
    return result;
}

void DocGen::load_json_from_file()
{
    std::ifstream file;
    file.open(m_json_filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << m_json_filename;
        std::cout << std::endl;
        exit(1);
    }
    m_jdata = json::parse(file);
    m_fdata = json_to_filedata(m_jdata);
    file.close();
}

bool DocGen::set_filenames()
{
    const std::string json_file_ext = ".json";
    const std::string wo_file_ext = ".txt";
    std::vector<std::string> files = get_files_in_current_directory();
    std::string file_path_str;
    for (std::string filename : files)
    {
        file_path_str = "./" + filename;
        std::filesystem::path filepath_obj = file_path_str;
        std::filesystem::path extension = filepath_obj.extension();
        if (extension.string() == json_file_ext)
            m_json_filename = filename;
        else if (is_valid_wo_file(filename))
            m_wo_filename = filename;
    }
    if (m_json_filename.empty() && !m_wo_filename.empty())
    {
        // JSON filename differs from WO by the extension
        m_json_filename =
            m_wo_filename.substr(
                0,
                m_wo_filename.find('.', 0) + 1);
        m_json_filename += json_file_ext;
    }
    if (m_wo_filename.empty())
    {
        std::cout << "Work Order file not found." << std::endl;
        return false;
    }
    return true;
}

/*
"[10 character wo number] - [EU name].txt"
*/
bool DocGen::is_valid_wo_file(const std::string &filename)
{
    if (filename.size() < 13)
        return false;
    if ((filename.substr(0, 3) == "ITI") &&
        (filename.substr(filename.size() - 4, 4) == ".txt"))
        return true;
    return false;
}

std::string DocGen::get_json_filename()
{
    const std::string json_file_ext = ".json";
    std::vector<std::string> files = get_files_in_current_directory();
    std::string file_path_str;
    for (std::string filename : files)
    {
        file_path_str = "./" + filename;
        std::filesystem::path filepath_obj = file_path_str;
        std::filesystem::path extension = filepath_obj.extension();
        if (extension.string() == json_file_ext)
            return filename;
    }
    return "";
}

void DocGen::set_appointment_date(const std::string &date)
{
    // Set appointment date in data
    m_fdata.appointment_date = date;
    // Check if JSON data is populated
    if (m_jdata.is_null())
        load_json_from_file();
    // Set appointment date in JSON data
    m_jdata["appointment date"] = date;
    // Overwrite JSON file with new data
    save_json_to_file();
}

std::string DocGen::get_appointment_date_from_input()
{
    std::string date;
    std::cout << "Enter appointment date: " << std::endl;
    getline(std::cin, date);
    while (!m_email_generator.is_valid_date(date))
    {
        std::cout << "\nAppointment date must have form ";
        std::cout << "MM/DD/YYYY HH:MM" << std::endl;
        std::cout << "Enter appointment date:" << std::endl;
        ;
        getline(std::cin, date);
    }
    return date;
}

void DocGen::print_help_message()
{
    std::cout << "Document Generator v2" << std::endl;
    std::cout << "\t\'w\' -> generate work order notes file ";
    std::cout << "(default behavior)\n";
    std::cout << "\t\'e\' -> append email to work order notes file\n";
    std::cout << "\t\'s\' -> set appointment date";
    std::cout << " (must in form MM/DD/YYYY HH:MM)\n";
    std::cout << "\t\'h\' -> show this message\n";
    std::cout << std::flush;
}