#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SDL3/SDL.h"

int main() {
    glm::vec3 position(0.0f, 1.0f, 2.0f);
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        SDL_Log("sdl failed to initialize with error %s", SDL_GetError());
        return -1;
    }
    SDL_Log("Initialised SDL");
    SDL_Window* window = SDL_CreateWindow("title", 1200, 720, 0);
    if (!window) {
        SDL_Log("failed to create window with error %s", SDL_GetError());
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderDrawColor(renderer,0xFF,0,0xFF,0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    return 0;
}
