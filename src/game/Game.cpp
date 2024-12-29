#include "Game.h"
#include "Crops/BaseCrop.h"
#include "InputHandler.h"

#include <mutex>

#define input InputHandler::getInstance()

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
      textures(ren.getSDLRenderer()) {
    ticks_per_second = 20;
    gridWidth = 16;
    gridHeight = 16;
    textures.InitializeTextures();
    tiles.resize(gridHeight);
    for (int i = 0; i < gridHeight; ++i) {
        tiles[i].resize(gridWidth);
        for (int j = 0; j < gridWidth; ++j) {
            SDL_Texture* dirtTexture = textures.GetTexture("wheat");
            if (dirtTexture) {
                tiles[i][j] = std::make_unique<BaseCrop>(dirtTexture);
            } else {
                std::cerr << "Failed to create tile due to texture loading error" << std::endl;
            }
        }
    }

}

Game::~Game() {}

void Game::OnTileClick(int x, int y) {
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
        auto& tile = tiles[y][x];
        tile->OnClick();
        printf("Tile (%d, %d) clicked\n", x, y);
    }
}

void Game::DrawTiles() {
    int screenWidth, screenHeight;
    SDL_GetCurrentRenderOutputSize(renderer.getSDLRenderer(), &screenWidth, &screenHeight);

    float tileWidth = static_cast<float>(screenWidth) / gridWidth;
    float tileHeight = static_cast<float>(screenHeight) / gridHeight;

    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            SDL_FRect tileRect = { x * tileWidth, y * tileHeight, tileWidth, tileHeight };
            tiles[y][x]->SetPosition(tileRect);
            //SDL_RenderTexture(renderer.getSDLRenderer(),  tiles[y][x]->GetTexture(), nullptr, &tileRect);
            tiles[y][x]->Draw(renderer.getSDLRenderer(), tileRect);
        }
    }
}

void Game::DrawDebugMenu() {
    ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoSavedSettings);

    ImGui::Text("test");
    ImGui::SliderInt("ticks per second", &ticks_per_second, 1, 100, "%d");

    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    DrawFormattedText(draw, ImVec2(50, 100), ImColor(255, 255, 255, 255), "frame count %d", total_frames);
    DrawFormattedText(draw, ImVec2(50, 112), ImColor(255, 255, 255, 255), "tick count %d", total_ticks);

    ImGui::End();
}

bool Game::Start() {
    isRunning = true;

    gameThread = std::thread([&]() {
        ticks_per_second = 20;
        total_ticks = 0;
        total_frames = 0;
        Uint32 lastTickTime = SDL_GetTicks();

        while (isRunning) {
            const Uint32 tickInterval = 1000 / ticks_per_second;
            Uint32 currentTime = SDL_GetTicks();
            Uint32 deltaTime = currentTime - lastTickTime;

            if (deltaTime >= tickInterval) {
                lastTickTime += tickInterval;
                total_ticks++;
            }

            if (input->isMouseButtonDown(0)) {
                int mousex,mousey;
                input->getMousePosition(mousex,mousey);
                int tileX = mousex/ (renderer.getWindowSize().x / gridWidth);
                int tileY = mousey  / (renderer.getWindowSize().y / gridHeight);

                OnTileClick(tileX, tileY);
            }

            total_frames++;
        }
    });

    renderer.render([&]() {
        DrawTiles();
        DrawDebugMenu();
    });

    return 0;
}
