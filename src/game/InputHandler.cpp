//
// Created by max on 12/25/2024.
//

#include "InputHandler.h"
#include <stdio.h>

InputHandler* InputHandler::instance = nullptr;

void InputHandler::UpdateFromEvent(const SDL_Event* event) {
    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            printf("key down %c\n",event->key.key);
            keyStates[event->key.key] = true;
        break;

        case SDL_EVENT_KEY_UP:
            keyStates[event->key.key] = false;
        break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                mouseButtonStates[0] = true;
            } else if (event->button.button == SDL_BUTTON_MIDDLE) {
                mouseButtonStates[1] = true;
            } else if (event->button.button == SDL_BUTTON_RIGHT) {
                mouseButtonStates[2] = true;
            }
        break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event->button.button == SDL_BUTTON_LEFT) {
                mouseButtonStates[0] = false;
            } else if (event->button.button == SDL_BUTTON_MIDDLE) {
                mouseButtonStates[1] = false;
            } else if (event->button.button == SDL_BUTTON_RIGHT) {
                mouseButtonStates[2] = false;
            }
        break;

        case SDL_EVENT_MOUSE_MOTION:
            mouseX = event->motion.x;
            mouseY = event->motion.y;
        break;

        default:
            break;
    }
}


bool InputHandler::isKeyPressed(SDL_Keycode key) const {
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

bool InputHandler::isMouseButtonDown(int button) const {
    if (button < 0 || button >= 3) {
        return false;
    }
    return mouseButtonStates[button];
}

void InputHandler::getMousePosition(int& x, int& y) const {
    x = mouseX;
    y = mouseY;
}
