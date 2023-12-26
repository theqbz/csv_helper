enable_testing()

add_executable( csv_validator
    "csv/IAnalyzer.h"
    "csv/Analyzer.h"
    "csv/Analyzer.cpp"
    "csv/IParser.h"
    "csv/Parser.h"
    "csv/Parser.cpp"
    "data/ConsoleArguments.h"
    "data/CsvData.h"
    "data/IniFile.h"
    "data/Ranges.h"
    "data/Report.h"
    "data/Result.h"
    "data/SettingData.h"
    "display/IDisplay.h"
    "display/Grid.h"
    "display/Grid.cpp"
    "display/Lines.h"
    "display/Lines.cpp"
    "display/IReporter.h"
    "display/Reporter.h"
    "display/Reporter.cpp"
    "parser/Console.h"
    "parser/Console.cpp"
    "parser/IniFile.h"
    "parser/IniFile.cpp"
    "task/ITask.h"
    "task/ConfigTask.h"
    "task/ConfigTask.cpp"
    "task/CsvTask.h"
    "task/CsvTask.cpp"
    "task/HelpTask.h"
    "task/HelpTask.cpp"
    "task/TaskFactory.h"
    "task/TaskFactory.cpp"
    "utils/IFileHandler.h"
    "utils/FileHandler.h"
    "utils/FileHandler.cpp"
    "utils/ISettings.h"
    "utils/Settings.h"
    "utils/Settings.cpp"
    "utils/Utility.h"
    "main.cpp"
)

set_property( TARGET csv_validator PROPERTY CXX_STANDARD 20 )

target_link_libraries( csv_validator PUBLIC
    CONAN_PKG::ftxui
    CONAN_PKG::gtest
)

include( GoogleTest )

