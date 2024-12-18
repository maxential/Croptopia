//
// Created by max on 12/10/2024.
//

#ifndef GAME_H
#define GAME_H

#include "../utilities/ConsoleManager.h"
#include "../renderer/Renderer.h"
#include "../renderer/TextureManager.h"
#include "Crops/BaseCrop.h"

// Move this soon
class Tomato : public BaseCrop {
public:

};

class Game {
public:
    Game(Renderer& ren);
    ~Game();
    bool Start();

private:
    /* Debug Stuff */
    void DrawDebugMenu();
    /* Rendering */
    /* Game Logic*/
    void Update();
    void update_crops();

    Renderer& renderer;
    TextureManager textures;

    std::thread gameThread;
    bool isRunning = false;

    const bool* key_states;

    int ticks_per_second;
    Uint32 tickInterval;
    Uint64 total_ticks;
    Uint64 total_frames;
};



#endif //GAME_H
