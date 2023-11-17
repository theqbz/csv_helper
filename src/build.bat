:: Add to Vim the "build and run the project with one keystroke" functionality
:: To use this script, start Vim from VS command promt and bind a key to run
:: this batch file
:: (QBZ 2023)

@ECHO Build and run CSV-HELPER project:

:build
@cd d:\repos\csvvalidator\build\
ninja
@IF %ERRORLEVEL% NEQ 0 GOTO end

:run
@ECHO start program
@start cmd /c bin\csv_helper.exe

:end
@cd d:\repos\csvvalidator\src\
@ECHO end script
