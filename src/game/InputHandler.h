//
// Created by max on 12/25/2024.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "SDL3/SDL.h"
#include <unordered_map>
#include <stdio.h>

class InputHandler {
public:
    static InputHandler* getInstance() {
        if (instance == nullptr) {
            instance = new InputHandler();
        }
        return instance;
    }

    void UpdateFromEvent(const SDL_Event* event);

    bool isKeyPressed(SDL_Keycode key) const;
    bool isMouseButtonDown(int button) const;
    void getMousePosition(int& x, int& y) const;

private:
    InputHandler() = default;
    ~InputHandler() = default;

    static InputHandler* instance;

    std::unordered_map<SDL_Keycode, bool> keyStates;
    bool mouseButtonStates[3] = {false, false, false}; // Left, Middle, Right
    int mouseX = 0;
    int mouseY = 0;
};


#endif //INPUTHANDLER_H
