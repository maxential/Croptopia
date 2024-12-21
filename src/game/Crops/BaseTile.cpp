//
// Created by max on 12/12/2024.
//

#include "BaseTile.h"

BaseTile::BaseTile(SDL_Texture* tex) : texture(tex) {
    position = {0, 0, 0, 0};
}
BaseTile::~BaseTile() {
    
}


void BaseTile::SetPosition(const SDL_FRect& pos) {
    position = pos;
}

SDL_Texture* BaseTile::GetTexture(){
    return texture;
}

void BaseTile::Draw(SDL_Renderer* renderer, const SDL_FRect& rect) {
    if (texture) {
        SDL_RenderTexture(renderer, texture, nullptr, &rect);
    }
}