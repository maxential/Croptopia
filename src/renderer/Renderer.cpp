//
// Created by max on 12/10/2024.
//

#include "Renderer.h"

Renderer::Renderer(Window& _window)
    : window(&_window)
{

    renderer = SDL_CreateRenderer(window->getSDLWindow(), NULL);
    if (!renderer) {
        SDL_Log("Failed to create renderer with error %s", SDL_GetError());
    }
}

Renderer::~Renderer()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
}

void Renderer::render(const std::function<void()>& callback)
{
    SDL_Log("starting render loop");

    ImGui::CreateContext();
    ImGui_ImplSDL3_InitForSDLRenderer(
        window->getSDLWindow(),
        renderer
    );
    ImGui_ImplSDLRenderer3_Init(renderer);
    ImGui::GetIO().IniFilename = nullptr;

    SDL_Event event;
    int quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    SDL_Log("quit");
                quit = 1;
                break;
            }
            ImGui_ImplSDL3_ProcessEvent(&event);
        }

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        ImGui::NewFrame();

        callback();

        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }


    SDL_Log("shutdown");
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

glm::i32vec2 Renderer::getWindowSize() {
    glm::i32vec2 size;
    SDL_GetCurrentRenderOutputSize(renderer, &size.x, &size.y);
    return size;
}