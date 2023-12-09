enable_testing()

add_executable( csv_validator
    "csv/IParser.h"
    "csv/Parser.h"
    "csv/Parser.cpp"
    "csv/Analyzer.h"
    "csv/Analyzer.cpp"
    "data/ConsoleArguments.h"
    "data/CsvData.h"
    "data/CsvData.cpp"
    "data/IniFile.h"
    "data/Result.h"
    "data/Result.cpp"
    "data/SettingData.h"
    "data/Report.h"
    "display/Reporter.h"
    "display/Reporter.cpp"
    "display/IDisplay.h"
    "display/Lines.h"
    "display/Lines.cpp"
    "display/Grid.h"
    "display/Grid.cpp"
    "parser/Console.h"
    "parser/Console.cpp"
    "parser/IniFile.h"
    "parser/IniFile.cpp"
    "utils/IFileHandler.h"
    "utils/FileHandler.h"
    "utils/FileHandler.cpp"
    "utils/ISettings.h"
    "utils/Settings.h"
    "utils/Settings.cpp"
    "main.cpp"
)

set_property( TARGET csv_validator PROPERTY CXX_STANDARD 20 )

target_link_libraries( csv_validator PUBLIC
    CONAN_PKG::ftxui
    CONAN_PKG::gtest
)

include( GoogleTest )

