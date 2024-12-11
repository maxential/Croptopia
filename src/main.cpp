
#include "game/Game.h"

int main() {
    /* Move this soon */
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        SDL_Log("sdl failed to initialize with error %s", SDL_GetError());
        return -1;
    }

    Window wind = Window("Croptopia Demo", 800, 600);
    Renderer rend = Renderer(wind);
    Game game = Game(rend);

    game.Start();

    // rend.render([&]() {
    //     SDL_SetRenderDrawColor(rend.getSDLRenderer(), 255, 0, 0, 255);
    //     SDL_FRect src_r;
    //     src_r.x = 0;
    //     src_r.y = 0;
    //     src_r.w = 128;
    //     src_r.h = 128;
    //
    //     SDL_FRect rect;
    //     rect.x = 100;
    //     rect.y = 100;
    //     rect.w = 200;
    //     rect.h = 150;
    //
    //
    //     SDL_RenderFillRect(rend.getSDLRenderer(), &rect);
    //     glm::vec4 color = { 255,0,255,255 };
    //     // draw::rectangle(rend.getSDLRenderer(), rect, color);
    //     //
    //     // bool render = SDL_RenderTexture(rend.>getSDLRenderer(), texture_manager->GetTexture("wheat"), &src_r, &src_r);
    //     // if (!render)
    //     // {
    //     //     SDL_Log("failed to render %s\n", SDL_GetError());
    //     //     return -1;
    //     // }
    //     //
    //     // DrawDebugMenu();
    //
    // });
    return 0;
}
