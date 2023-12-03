enable_testing()

add_executable( csv_helper
    "utils/parser/data/ConsoleArguments.h"
    "utils/parser/data/IniFile.h"
    "utils/parser/Console.h"
    "utils/parser/Console.cpp"
    "utils/parser/IniFile.h"
    "utils/parser/IniFile.cpp"
    "utils/IFileHandler.h"
    "utils/FileHandler.h"
    "utils/FileHandler.cpp"
    "utils/ISettings.h"
    "utils/Settings.h"
    "utils/Settings.cpp"
    "csv/Data.h"
    "csv/IParser.h"
    "csv/Parser.h"
    "csv/Parser.cpp"
    "csv/Analyzer.h"
    "main.cpp"
)

set_property( TARGET csv_helper PROPERTY CXX_STANDARD 20 )

target_link_libraries( csv_helper PUBLIC
    CONAN_PKG::ftxui
    CONAN_PKG::gtest
)

include( GoogleTest )

