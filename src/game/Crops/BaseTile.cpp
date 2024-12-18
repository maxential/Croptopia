//
// Created by max on 12/12/2024.
//

#include "BaseTile.h"

void BaseTile::SetPosition(const SDL_FRect& pos) {
    position = pos;
}

SDL_Texture* BaseTile::GetTexture(){
    return texture;
}