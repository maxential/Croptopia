//
// Created by max on 12/10/2024.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <memory>
#include <functional>
#include "Window.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"

class Renderer
{
public:
    Renderer(Window& _window);
    ~Renderer();

    SDL_Renderer* getSDLRenderer() const { return renderer; }

    void render(const std::function<void()>& callback);

private:
    std::unique_ptr<Window> window;
    SDL_Renderer* renderer;
};



#endif //RENDERER_H