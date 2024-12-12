//
// Created by max on 12/12/2024.
//

#include "TextureManager.h"
#include "SDL3/SDL_image.h"
#include <filesystem>

namespace fs = std::filesystem;

TextureManager::TextureManager(SDL_Renderer* _renderer) : renderer(_renderer)
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::CleanupTextures()
{
    for (auto& pair : textures)
    {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}

void TextureManager::AddTexture(const std::string& name, SDL_Texture* texture)
{
    std::lock_guard<std::mutex> lock(textureMapMutex);
    textures[name] = texture;
}

SDL_Texture* TextureManager::GetTexture(const std::string& name)
{
    std::lock_guard<std::mutex> lock(textureMapMutex);
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    else {
        SDL_Log("Texture not found: %s", name.c_str());
        return nullptr;
    }
}

bool TextureManager::InitializeTextures() // turn this into a std::map of std::string of texture name and sdl_textures.
{
    SDL_Log("Initializing textures");

    // fs::path cropsPath = "assets/crops";
    fs::path basePath = fs::current_path();
    fs::path cropsPath = basePath / ".." / ".." / "assets" / "crops";

    // Normalize the path to resolve any ".."
    cropsPath = cropsPath.lexically_normal();

    if (!fs::exists(cropsPath) || !fs::is_directory(cropsPath))
    {
        SDL_Log("Crops folder does not exist or is not a directory.");
        return false;
    }

    for (const auto& entry : fs::directory_iterator(cropsPath))
    {
        if (entry.is_regular_file())
        {
            std::string fileName = entry.path().filename().string();

            SDL_Surface* srfimg = IMG_Load(entry.path().string().c_str());
            if (!srfimg)
            {
                SDL_Log("Failed to load image %s: %s", fileName.c_str(), SDL_GetError());
                continue;
            }

            SDL_Texture* surface_texture = SDL_CreateTextureFromSurface(renderer, srfimg);
            SDL_DestroySurface(srfimg);
            if (!surface_texture)
            {
                SDL_Log("Failed to create texture from %s: %s", fileName.c_str(), SDL_GetError());
                continue;
            }

            std::string textureName = fileName.substr(0, fileName.find_last_of('.'));
            textures[textureName] = surface_texture;
        }
    }

    return true;
}