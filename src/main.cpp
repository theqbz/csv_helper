///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  main.h
/// @brief csvvalidator
///
/// This program can analyze the provided csv files, seeking for errors. It can
/// detect Records that occur more than once and if a Record contains more or
/// less Fileds than the number of Labels. (The Analyzer identifies Label list
/// in the first non empty row of the file!)
///

#include "data/ConsoleArguments.h"
#include "data/IniFile.h"
#include "parser/Console.h"
#include "parser/IniFile.h"
#include "task/TaskFactory.h"
#include "utils/Settings.h"
#include "utils/Utility.h"
#include "utils/programpath/WindowsPath.h"

#include <iostream>

// #define DEBUG 1

int main(int argc, const char* argv[])
{

#ifdef DEBUG
    std::cout << "Debug mode. Press ENTER to start!\n";
    std::cin.get();
#endif // DEBUG

    std::cout << "* CsvValidator by QBZ * version: 1.0\n";
    csvvalidator::utils::setConfigPath(csvvalidator::utils::Program::absolutePath());
    csvvalidator::data::console::Arguments consoleArgs { csvvalidator::parser::Console::parse(argc, argv) };
    csvvalidator::data::ini::File inifile { csvvalidator::parser::IniFile::parse(csvvalidator::utils::INI_FILE_NAME) };
    csvvalidator::utils::Settings settings(consoleArgs.m_parameters, inifile.m_content);
    csvvalidator::task::TaskFactory taskFactory(settings, consoleArgs);
    taskFactory.runTasks();

#ifdef DEBUG
    std::cout << "\nEnd program. Press ENTER to exit!\n";
    std::cin.get();
#endif // DEBUG

    return 0;
}
