//
// Created by max on 12/12/2024.
//

#ifndef BASETILE_H
#define BASETILE_H
#include "BaseEntity.h"

class BaseTile : public BaseEntity {
private:
    SDL_Texture* texture;
    SDL_FRect position;
public:
    void SetPosition(const SDL_FRect& pos);
    SDL_Texture* GetTexture();
};



#endif //BASETILE_H
