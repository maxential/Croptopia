//
// Created by max on 12/10/2024.
//
#include "Game.h"

/* Move this soon */
void DrawFormattedText(ImDrawList* drawList, const ImVec2& pos, ImU32 color, const char* format, ...) {
    char buffer[512];

    va_list args;
    va_start(args, format);
    std::vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    drawList->AddText(pos, color, buffer);
}

Game::Game(Renderer& ren)
      : renderer(ren),
        textures(ren.getSDLRenderer())
{
    ticks_per_second = 20;

    textures.InitializeTextures();
};

Game::~Game()
{

}

void Game::DrawDebugMenu()
{
    ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoSavedSettings);

    ImGui::Text("test");
    ImGui::SliderInt("ticks per second", &ticks_per_second, 1, 100, "%d");

    ImDrawList* draw = ImGui::GetBackgroundDrawList();

    DrawFormattedText(draw, ImVec2(50, 100), ImColor(255, 255, 255, 255), "frame count %d", total_frames);
    DrawFormattedText(draw, ImVec2(50, 112), ImColor(255, 255, 255, 255), "tick count %d", total_ticks);
    ImGui::End();
}

bool Game::Start()
{
    isRunning = true;
    // Game loop
    gameThread = std::thread([&]() {
        ticks_per_second = 20;
        total_ticks = 0;
        total_frames = 0;
        Uint32 lastTickTime = SDL_GetTicks();
        Uint32 lastFrameTime = lastTickTime;

        while (isRunning) { // Check the running condition
            const Uint32 tickInterval = 1000 / ticks_per_second;
            Uint32 currentTime = SDL_GetTicks();
            Uint32 deltaTime = currentTime - lastTickTime;

            if (deltaTime >= tickInterval) {
                lastTickTime += tickInterval;
                total_ticks++;
                // update();
                //printf("tick! %d\n", lastTickTime);
            }
            // printf("frame!\n");
            total_frames++;
            SDL_Delay(4);
        }
    });

    renderer.render([&]() {
         SDL_SetRenderDrawColor(renderer.getSDLRenderer(), 255, 0, 0, 255);
         SDL_FRect src_r;
         src_r.x = 0;
         src_r.y = 0;
         src_r.w = 128;
         src_r.h = 128;

         SDL_FRect rect;
         rect.x = 100;
         rect.y = 100;
         rect.w = 200;
         rect.h = 150;

         SDL_RenderFillRect(renderer.getSDLRenderer(), &rect);
         glm::vec4 color = { 255,0,255,255 };

        DrawDebugMenu();
    });


    return 0;
}