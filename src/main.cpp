#include <concepts>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Provide a file with the arguments
// Opent the csv file and parse it line by line
// The first line goning to be the label-list
// The other lines have to fit to this label line
// Count fields in every line and compare to the number of fields in the label-list
// If there is difference, sing it in the begining of the line
// Print the content of the lines to the screen with the following format:
// label: value | label: value | etc...

const std::string DEBUG_TEST_FILE = "d:\\temp\\csv-helper-test.csv";

typedef std::vector<std::string> Row;
typedef std::vector<Row> Table;
typedef std::pair<int, Row> FileLine;
typedef std::vector<FileLine> FileContent;

const char LINE_NUMBER_SPACING = ' ';
const char DELIMITER           = ';';

class Settings
{
public:
    enum class LabelPosition
    {
        Top,
        Inline
    };

    enum class DiffDetectMode
    {
        Off,
        Auto,
        Above,
        Below
    };

    Settings()                = default;
    Settings(const Settings&) = delete;
    Settings(Settings&&)      = default;
    inline void linesAroundErrors(const unsigned int p_value) { m_linesAroundErrors = p_value; }
    inline unsigned int linesAroundErrors() const { return m_linesAroundErrors; }
    inline void labelPosition(const LabelPosition p_position) { m_labelPosition = p_position; }
    inline LabelPosition labelPosition() const { return m_labelPosition; }
    inline void emptyFields(const unsigned char p_placeholder) { m_emptyFields = p_placeholder; }
    inline unsigned char emptyFields() const { return m_emptyFields; }
    inline void emptyLines(const unsigned char p_placeholder) { m_emptyLines = p_placeholder; }
    inline unsigned char emptyLines() const { return m_emptyLines; }
    inline void tableOutput(const bool p_value) { m_tableOutput = p_value; }
    inline bool tableOutput() const { return m_tableOutput; }
    inline void diffDetectMode(const DiffDetectMode p_mode) { m_diff = p_mode; }
    inline DiffDetectMode diffDetectMode() const { return m_diff; }

private:
    unsigned int m_linesAroundErrors = 0;                   // sohw number of lines around errors (0: show all lines)
    LabelPosition m_labelPosition    = LabelPosition::Top;  // top / inline (This option and TalbeOutput are mutually exclusive: if TableOutput is true, it inactivates this setting.)
    unsigned char m_emptyFields      = '.';                 // placeholder for empty values (0: skip empty values)
    unsigned char m_emptyLines       = 0;                   // placeholder for empty lines (0: skip empty lines / 1: show as error empty lines)
    bool m_tableOutput               = false;               // show output in a table (This option and LabelPosiotion are mutually exclusive: if this is true, it inactivates LabelPosition setting.)
    DiffDetectMode m_diff            = DiffDetectMode::Off; // off / auto / above / below
};

class Result
{
public:
    Result()              = default;
    Result(const Result&) = delete;
    Result(Result&&)      = default;

    inline void labels(const Row& p_labels) { m_labels = p_labels; }
    inline Row labels() const { return m_labels; }
    inline void content(const Table& p_content) { m_content = p_content; }
    inline Table content() const { return m_content; }
    inline void errors(const Row& p_errors) { m_errors = p_errors; }
    inline void addError(const std::string p_error) { m_errors.push_back(p_error); }
    inline Row errors() const { return m_errors; }

private:
    Row m_labels {};
    Table m_content {};
    Row m_errors {};
};

std::fstream openFile(const std::string& p_fileName)
{
    std::fstream file(p_fileName, std::ios::in);
    if (!file.good()) {
        std::cout << "ERROR: Can't open the file: " << p_fileName << "\n";
        return {};
    }
    std::cout << "File OK: " << p_fileName << "\n";
    return file;
}

FileLine parseLine(const std::string& p_line)
{
    if (p_line.length() == 0) {
        return {};
    }
    FileLine line {};
    size_t offset = 0, semicolonPos = 0;
    do {
        semicolonPos = p_line.find(DELIMITER, offset);
        line.second.push_back(p_line.substr(offset, semicolonPos - offset));
        offset = semicolonPos + 1;
        ++line.first;
    } while (semicolonPos < std::string::npos);
    return line;
}

FileContent parseFile(std::fstream p_file)
{
    if (p_file.peek() == std::char_traits<char>::eof()) {
        return {};
    }
    FileContent table {};
    std::string line;
    int lineCount = 0, emptyLineCount = 0;
    while (std::getline(p_file, line)) {
        ++lineCount;
        if (line.empty()) {
            ++emptyLineCount;
        }
        table.push_back(parseLine(line));
    }
    std::cout << "The file contains " << lineCount << " lines (" << emptyLineCount << " was empty).\n\n";
    p_file.close();
    return table;
}

void printErrors(const std::vector<std::string>& p_errors)
{
    if (p_errors.empty()) {
        std::cout << "\nNo p_errors found\n";
        return;
    }
    std::cout << "\nThe following p_errors found:\n";
    for (const std::string& err : p_errors) {
        std::cout << err << "\n";
    }
}

const std::string linePrefix(const size_t p_allLines, const size_t p_currentLineNumer)
{
    std::string prefix           = std::to_string(p_currentLineNumer);
    const size_t numberOfSpacing = std::to_string(p_allLines).length() - prefix.length();
    return prefix.insert(0, numberOfSpacing, LINE_NUMBER_SPACING);
}

void printResult(const FileContent& p_table)
{
    if (p_table.empty()) {
        return;
    }
    std::vector<std::string> errors {};
    const int labelCount   = p_table.at(0).first;
    const size_t lineCount = p_table.size();
    int lineNumber         = 1;
    for (const FileLine& line : p_table) {
        if (line.second.empty()) {
            ++lineNumber;
            continue;
        }
        std::string prefix     = " ";
        const size_t itemCount = line.first;
        if (labelCount != itemCount) {
            errors.push_back("ERROR at line " + std::to_string(lineNumber) + ": the line doesn't match to the label list. (values: " + std::to_string(itemCount) + " / " + std::to_string(labelCount) + ")");
            prefix = "*";
        }
        prefix += linePrefix(lineCount, lineNumber);
        std::cout << prefix << " >";
        bool prewiousWasEmpty = false;
        for (const std::string& item : line.second) {
            bool thisItemIsEmpty  = false;
            std::string separator = " | ";
            if (item.empty()) {
                thisItemIsEmpty = true;
            }
            if (!prewiousWasEmpty && thisItemIsEmpty) {
                separator        = " |.";
                prewiousWasEmpty = true;
            } else if (prewiousWasEmpty && thisItemIsEmpty) {
                separator        = ".";
                prewiousWasEmpty = true;
            } else if (prewiousWasEmpty && !thisItemIsEmpty) {
                separator        = "| ";
                prewiousWasEmpty = false;
            }
            std::cout << separator << item;
        }
        std::cout << "\n";
        ++lineNumber;
    }
    printErrors(errors);
}

void printArgHelp(const char* p_programName)
{
    std::cout << "No file presented.\n"
              << "To parse a file start the program with a filename:\n\n"
              << "\t>" << p_programName << "  path/to/file.csv\n\n";
}

int main(int argc, const char* argv[])
{
    std::string fileToTest { DEBUG_TEST_FILE };
    std::cout << "* CSV-HELPER BY QBZ * version: 1.0b\n";
    if (argc < 2) {
        // printArgHelp(argv[0]);
        // return 0;
    } else {
        fileToTest = argv[1];
    }
    printResult(parseFile(openFile(fileToTest)));
    std::cin.get();
    return 0;
}
