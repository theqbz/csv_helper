# CSV Validator

**This program can analyze the provided csv files, seeking for errors. It can detect Records that occur more than once and if a Record contains more or less Fileds than the number of Labels. (The Analyzer identifies Label list in the first non empty row of the file!)**

To parse a file, start the program with a filename or a path:

        csv_validator.exe  path/or/file  [settings]

To get help, use the `help` command!

To sore user's settings permanently, use `config` command!

## Settings:

| arg            | type     | possible values             | description                                                |
|----------------|----------|-----------------------------|------------------------------------------------------------|
| `-delimiter`   | (char)   | default value: `;`          | the delimiter between Fields in .csv file                  | 
| `-emptyLines`  | (string) | `skip`* / `error` / `leave` | defines what to do with empty lines                        |
| `-emptyFields` | (char)   | default value: `_`          | placeholder for empty values; <empty>: skip empty values   |
| `-label`       | (string) | `top`* / `inline`           | defines where to print the labels                          |
| `-errorLines`  | (int)    | default value: `0`          | the number of lines showed around errors (`-1`: all lines) |
| `-errorLevel`  | (string) | `all` / `error`*            | defines the verbosity of the error log                     |

*\* default values*

## Libraries

- FTXUI https://github.com/ArthurSonzogni/FTXUI</br>
  [![Conan Center](https://img.shields.io/conan/v/ftxui)](https://conan.io/center/recipes/ftxui)
- Gtest</br>
  [![Conan Center](https://img.shields.io/conan/v/gtest)](https://conan.io/center/recipes/gtest)
