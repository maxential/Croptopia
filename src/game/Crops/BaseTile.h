//
// Created by max on 12/12/2024.
//

#ifndef BASETILE_H
#define BASETILE_H
#include "BaseEntity.h"

class BaseTile {
protected:
    SDL_Texture* texture;
    SDL_FRect position;
public:
    BaseTile(SDL_Texture* tex);
    ~BaseTile();

    void SetPosition(const SDL_FRect& pos);
    SDL_Texture* GetTexture();
    virtual void Draw(SDL_Renderer* renderer, const SDL_FRect& rect) = 0;
    virtual void OnClick() = 0;
};



#endif //BASETILE_H
