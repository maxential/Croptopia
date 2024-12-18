//
// Created by max on 12/10/2024.
//
#include "Game.h"
#include "Crops/BaseTile.h"

int gridWidth = 16;   // gridWidth: number of tiles horizontally
int gridHeight = 16; // gridHeight: number of tiles vertically

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

    // Initialize tile grid
    std::vector<std::vector<BaseTile>> tiles(gridHeight, std::vector<BaseTile>(gridWidth));

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
            }

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;
                        ConsoleManager::getInstance()->log(WARNING_NONE, "test");
                        // Determine which tile is clicked
                        int tileX = mouseX / (renderer.getWindowSize().x / gridWidth);
                        int tileY = mouseY / (renderer.getWindowSize().y / gridHeight);

                        if (tileX >= 0 && tileX < gridWidth && tileY >= 0 && tileY < gridHeight) {
                            BaseTile& clickedTile = tiles[tileY][tileX];
                            printf("Clicked Tile: (%d, %d)\n", tileX, tileY);
                        }
                    }
                }
            }

            total_frames++;

        }
    });

    renderer.render([&]() {
        int screenWidth, screenHeight;
        SDL_GetCurrentRenderOutputSize(renderer.getSDLRenderer(), &screenWidth, &screenHeight);

        float tileWidth = static_cast<float>(screenWidth) / gridWidth;
        float tileHeight = static_cast<float>(screenHeight) / gridHeight;

        /* Draw background tiles */
        for (int y = 0; y < gridHeight; ++y) {
            for (int x = 0; x < gridWidth; ++x) {
                BaseTile& tile = tiles[y][x];
                SDL_FRect tileRect = { x * tileWidth, y * tileHeight, tileWidth, tileHeight };

                tile.SetPosition(tileRect);

                SDL_RenderTexture(renderer.getSDLRenderer(), textures.GetTexture("wheat"), nullptr, &tileRect);
            }
        }

        DrawDebugMenu();
    });

    return 0;
}
