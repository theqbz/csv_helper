enable_testing()

add_executable( csv_helper
    "parser/IConsole.h"
    "parser/Console.h"
    "parser/Console.cpp"
    "utils/ISettings.h"
    "utils/Settings.h"
    "main.cpp"
)

set_property( TARGET csv_helper PROPERTY CXX_STANDARD 20 )

target_link_libraries( csv_helper PUBLIC
    CONAN_PKG::ftxui
    CONAN_PKG::gtest
)

include( GoogleTest )

