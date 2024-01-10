# CSV VALIDATOR

This program can analyze the provided *csv* files, seeking for errors. It can
detect Records that occur more than once and if a Record contains more or less
Fileds than the number of Labels. (The Analyzer identifies Label list in the
first non empty row of the file!)


## Basics {#basics}

    > csv_validator.exe  [command/file/path]  [settings]

To parse a file, start the program with a filename or a path:

    > csv_validator.exe  path/or/file  [settings]

To get help, use the  `help`  command:

    > csv_validator.exe  help

To [store user's settings](#storesettings) permanently, use the  `config`  command:

    > csv_validator.exe  config  [settings]


### Settings {#settings}

| arg            | type   | possible values             | description                                                |
|----------------|--------|-----------------------------|------------------------------------------------------------|
| `-delimiter`   | char   | default: `;`                | the delimiter between Fields in .csv file                  | 
| `-emptyLines`  | string | `skip`* / `error` / `leave` | defines what to do with empty lines                        |
| `-emptyFields` | char   | default: `_`                | placeholder for empty values; <empty>: skip empty values   |
| `-labels`      | string | `top`* / `inline`           | defines where to print the labels                          |
| `-errorLines`  | int    | default: `0`                | the number of lines showed around errors (`-1`: all lines) |
| `-errorLevel`  | string | `all` / `error`*            | defines the verbosity of the error log                     |

*\* default value*

#### Detailed log {#settingsverbose}

To turn on detailed log, use `-verbose` setting.

The `-verbose` setting can be anywhere in the command, because it has no other
effect on the program apart from turning on verbose logging! This option can
only be used for the given start, it can't be permanently!

### Store settings {#storesettings}

The program can permanently store user's own settings in an .ini file. To use
this function start the program with the `config` command and provide the
settings to be store.

Multiple arguments can be specified. The `config` command with no arguments
creates a new .ini file with the default settings (or overwrites the existing
one).

