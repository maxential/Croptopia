//
// Created by max on 12/10/2024.
//

#ifndef GAME_H
#define GAME_H

#include "../renderer/Renderer.h"


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

    const bool* key_states;

    int ticks_per_second;
    Uint32 tickInterval;
    Uint64 total_ticks;
    Uint64 total_frames;
};



#endif //GAME_H
