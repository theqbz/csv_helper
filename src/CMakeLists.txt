enable_testing()

add_executable( csv_helper
    "utils/datastructure/Arguments.h"
    "utils/datastructure/IniData.h"
    "utils/datastructure/CsvData.h"
    "utils/IFileHandler.h"
    "utils/FileHandler.h"
    "utils/FileHandler.cpp"
    "utils/ISettings.h"
    "utils/Settings.h"
    "utils/Settings.cpp"
    "parser/IConsole.h"
    "parser/Console.h"
    "parser/Console.cpp"
    "parser/IIniFile.h"
    "parser/IniFile.h"
    "parser/IniFile.cpp"
    "main.cpp"
)

set_property( TARGET csv_helper PROPERTY CXX_STANDARD 20 )

target_link_libraries( csv_helper PUBLIC
    CONAN_PKG::ftxui
    CONAN_PKG::gtest
)

include( GoogleTest )

