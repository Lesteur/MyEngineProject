/**
 * @file Sprite.cpp
 * @brief Implementation of the Sprite class for converting indexed images to OpenGL textures.
 */

#include "core/Sprite.hpp"

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <SDL2/SDL.h>

namespace Engine
{
    SDL_Renderer * Sprite::renderer = nullptr;

    Sprite::Sprite(const Image& img, const Palette& pal) :
        width(static_cast<int>(img.width)),
        height(static_cast<int>(img.height))
    {
        // Create an array to hold the RGBA pixel data
        std::vector<uint8_t> rgbaPixels(width * height * 4);

        // Convert indexed pixels to RGBA using the palette
        for (unsigned int i = 0; i < img.width * img.height; ++i)
        {
            uint8_t index = img.pixels[i];
            if (index >= pal.size)
            {
                throw std::out_of_range("Pixel index out of palette bounds");
            }

            uint32_t color = pal.colors[index];
            rgbaPixels[i * 4 + 0] = (color >> 8) & 0xFF; // Blue
            rgbaPixels[i * 4 + 1] = (color >> 16) & 0xFF;  // Green
            rgbaPixels[i * 4 + 2] = (color >> 24) & 0xFF; // Red
            rgbaPixels[i * 4 + 3] = (color >> 0) & 0xFF;  // Alpha
        }

        SDL_Surface * surface = SDL_CreateRGBSurfaceFrom(
            rgbaPixels.data(),
            width,
            height,
            32,
            width * 4,
            0x00FF0000,
            0x0000FF00,
            0x000000FF,
            0xFF000000
        );

        if (!surface)
        {
            throw std::runtime_error("Failed to create SDL surface");
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!texture)
        {
            throw std::runtime_error("Failed to create SDL texture");
        }
    }

    Sprite::~Sprite()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

    SDL_Texture * Sprite::GetTexture() const
    {
        return texture;
    }

    int Sprite::GetWidth() const
    {
        return width;
    }

    int Sprite::GetHeight() const
    {
        return height;
    }
}