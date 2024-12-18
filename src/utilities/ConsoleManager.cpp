//
// Created by max on 12/17/2024.
//

#include "ConsoleManager.h"

// Initialize the static member
ConsoleManager* ConsoleManager::instance = nullptr;

void ConsoleManager::Initialize() {
    if (isInitialized) {
        std::cerr << "Console already initialized." << std::endl;
        return;
    }

    if (AllocConsole()) {
        FILE* stream;
        if (freopen_s(&stream, "CONOUT$", "w", stdout) != 0) {
            std::cerr << "Error redirecting standard output." << std::endl;
            return;
        }
        isInitialized = true;
        std::cout << "Console initialized successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to allocate console." << std::endl;
    }
}

void ConsoleManager::cleanup() {
    if (!isInitialized) {
        std::cerr << "[Hyperion]  Could not cleanup: Console not initialized." << std::endl;
        return;
    }

    ShowWindow(GetConsoleWindow(), SW_HIDE);
    FreeConsole();
    isInitialized = false;
}

