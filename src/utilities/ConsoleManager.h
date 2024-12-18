//
// Created by max on 12/17/2024.
//

#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H



#include <iostream>
#include <Windows.h>
#include <string>
#include <format>  // C++20 required for std::format
#include <string_view>  // To allow std::string_view for runtime format strings

/*
    Warning levels
*/
enum WARNING_LEVELS
{
    WARNING_NONE,
    WARNING_SUCCESS,
    WARNING_ERROR,
    WARNING_CRITICAL
};

class ConsoleManager {
private:
    static ConsoleManager* instance; // Singleton instance
    bool isInitialized;              // Tracks if the console is initialized

    // Private constructor to prevent instantiation
    ConsoleManager() : isInitialized(false) {}

    // Private destructor
    ~ConsoleManager() {}

    /*
        Color codes
    */
    const char* COLOR_DEFAULT = "\033[0m";   // Grey
    const char* COLOR_NONE = "\033[97m";     // White
    const char* COLOR_SUCCESS = "\033[32m";  // Green
    const char* COLOR_ERROR = "\033[33m";    // Yellow
    const char* COLOR_CRITICAL = "\033[31m"; // Red
    const char* COLOR_DARK = "\033[90m"; // Red

    inline void log_impl(int warning_level, const char* format, va_list args)
    {
#ifdef _WIN32
        // Enable ANSI escape codes in Windows Command Prompt
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        if (hConsole == INVALID_HANDLE_VALUE || !GetConsoleMode(hConsole, &mode)) {
            return;
        }
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

        // Print the warning level and set the color to console
        switch (warning_level)
        {
        case WARNING_NONE:
            printf("%s[Hyperion]  ", COLOR_NONE);
            break;
        case WARNING_SUCCESS:
            printf("%s[Hyperion]  %s", COLOR_SUCCESS, COLOR_NONE);
            break;
        case WARNING_ERROR:
            printf("%s[Hyperion]  %s", COLOR_ERROR, COLOR_NONE);
            break;
        case WARNING_CRITICAL:
            printf("%s[Hyperion]  %s", COLOR_CRITICAL, COLOR_NONE);
            break;
        default:
            printf("%s[Hyperion]  ", COLOR_NONE);
            break;
        }

        vprintf(format, args);

        printf("%s\n", COLOR_DEFAULT);
    }

public:
    // Get the singleton instance
    static ConsoleManager* getInstance() {
        if (instance == nullptr) {
            instance = new ConsoleManager();
        }
        return instance;
    }

    // Initialize the console
    void Initialize();

    // Cleanup the console
    void cleanup();

    // Variadic log function with custom warning level
    inline void log(int warning_level, const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        log_impl(warning_level, format, args);
        va_end(args);
    }
};

#define console ConsoleManager::getInstance()



#endif //CONSOLEMANAGER_H
