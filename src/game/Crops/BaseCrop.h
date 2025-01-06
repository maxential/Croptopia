//
// Created by max on 12/12/2024.
//

#ifndef BASECROP_H
#define BASECROP_H

#include "BaseTile.h"
#include <stdio.h>
#include <string>

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
        BaseTile::Draw(renderer, rect);
    }

    void OnClick() override {
        Grow();
        printf("Crop grow stage: %d\n", grow_stage);
    }

    virtual std::string GetType() const = 0; // Ensure derived classes define their type
};



#endif //BASECROP_H
