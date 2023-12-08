///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  main.h
/// @brief csvvalidator
///

#include "csv/Analyzer.h"
#include "csv/Parser.h"
#include "data/ConsoleArguments.h"
#include "data/CsvData.h"
#include "data/Result.h"
#include "data/SettingData.h"
#include "display/Lines.h"
#include "parser/Console.h"
#include "utils/FileHandler.h"
#include "utils/Settings.h"

#include <iostream>

const std::string DEBUG_TEST_FILE = "d:\\temp\\csv-helper-test.csv";

void testRun(const std::string& p_file, csvvalidator::data::SettingData p_consoleArgs)
{
    csvvalidator::data::SettingData iniFile;
    csvvalidator::utils::Settings settings(p_consoleArgs, iniFile);
    settings.init();
    csvvalidator::utils::FileHandler file(p_file);
    csvvalidator::csv::Parser csvParser(settings);
    csvvalidator::csv::Analyzer csvAnalyzer(settings);
    csvvalidator::data::csv::File csvFile          = csvParser.process(file);
    csvvalidator::data::csv::Result analysisResult = csvAnalyzer.process(csvFile);
    csvvalidator::display::Lines display(settings);
    display.render(csvFile.getTable(settings), analysisResult.getTable(settings));
}

void printArgHelp(const char* p_programName)
{
    std::cout << "No file presented.\n"
              << "To parse a file start the program with a filename:\n\n"
              << "\t>  " << p_programName << "  path/to/file.csv  [settings]\n\n";
}

int main(int argc, const char* argv[])
{
    std::string fileToTest { DEBUG_TEST_FILE };
    std::cout << "* CsvValidator by QBZ * version: 1.0b\n";
    if (argc < 2) {
        // printArgHelp(argv[0]);
    } else {
        fileToTest = argv[1];
    }
    csvvalidator::data::console::Arguments consoleArgs = csvvalidator::parser::Console::parse(argc, argv);
    testRun(fileToTest, consoleArgs);
    std::cout << "\nEnd program. Press ENTER to exit!\n";
    std::cin.get();
    return 0;
}
