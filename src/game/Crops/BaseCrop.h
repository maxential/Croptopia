//
// Created by max on 12/12/2024.
//

#ifndef BASECROP_H
#define BASECROP_H

#include "BaseTile.h"
#include <stdio.h>

class BaseCrop : public BaseTile {
public:
    BaseCrop(SDL_Texture* tex) : BaseTile(tex) {
        position = {0, 0, 0, 0};
    }
    int grow_time;
    int grow_stage;

    virtual void Grow() {
        grow_stage++;
    }

    void Draw(SDL_Renderer* renderer, const SDL_FRect& rect) override {
        // // The crop's color changes as it grows (example: fading green)
        // SDL_SetRenderDrawColor(renderer, 0, 255 - grow_stage * 20, 0, 255); // Gradually less green
        // SDL_RenderFillRect(renderer, &rect);  // Fill the rectangle with the crop's color
        BaseTile::Draw(renderer, rect);
    }

    void OnClick() override {
        Grow();
        printf("Crop grow stage: %d\n", grow_stage);
    }
};



#endif //BASECROP_H
