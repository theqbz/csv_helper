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
#include "data/Report.h"
#include "data/Result.h"
#include "data/SettingData.h"
#include "display/Lines.h"
#include "display/Reporter.h"
#include "parser/Console.h"
#include "task/ITask.h"
#include "task/TaskFactory.h"
#include "utils/FileHandler.h"
#include "utils/Settings.h"

#include <ios>
#include <iostream>
#include <string>

const std::string DEBUG_TEST_FILE = "d:\\temp\\csv-helper-test.csv";

static void testRun(const std::string& p_file, csvvalidator::data::SettingData p_consoleArgs)
{
    csvvalidator::data::SettingData iniFile;
    csvvalidator::utils::Settings settings(p_consoleArgs, iniFile);
    csvvalidator::utils::FileHandler file(p_file);
    csvvalidator::csv::Parser csvParser(settings);
    csvvalidator::csv::Analyzer csvAnalyzer(settings);
    csvvalidator::data::csv::File csvFile          = csvParser.process(file);
    csvvalidator::data::csv::Result analysisResult = csvAnalyzer.process(csvFile);
    csvvalidator::display::Reporter reporter(settings);
    csvvalidator::data::display::Report report = reporter.process(csvFile, analysisResult);
    csvvalidator::display::Lines display(settings);
    display.render(report);
    std::exit(0);
}

static void printNoArgHelp(const char* p_programName)
{
    std::cout << "No file presented.\n"
              << "To parse a file start the program with a filename:\n\n"
              << "\t>  " << p_programName << "  path/to/file.csv  [settings]\n\n"
              << "To get help, use the  -help  flag!\n\n";
}

int main(int argc, const char* argv[])
{
    std::cin.get();
    std::cout << "* CsvValidator by QBZ * version: 1.0b\n";
    csvvalidator::data::console::Arguments consoleArgs = csvvalidator::parser::Console::parse(argc, argv);
    // std::string fileToTest { DEBUG_TEST_FILE };
    // testRun(fileToTest, consoleArgs);
    csvvalidator::data::SettingData iniFile;
    csvvalidator::utils::Settings settings(consoleArgs.m_parameters, iniFile);
    csvvalidator::task::TaskFactory taskFactory(consoleArgs, settings);
    bool success = taskFactory.runTasks();
    std::cout << "Tasks execution was " << (success ? "success\n" : "fail\n");
    std::cout << "\nEnd program. Press ENTER to exit!\n";
    std::cin.get();
    return 0;
}
