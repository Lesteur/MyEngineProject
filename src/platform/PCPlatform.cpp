/**
 * @file PCPlatform.cpp
 * @brief Implementation of the PCPlatform class for PC systems using OpenGL 3.3.
 */
#include "platform/PCPlatform.hpp"
#include "core/Sprite.hpp"

#include <SDL2/SDL.h>

#include <chrono>
#include <thread>
#include <stdexcept>
#include <iostream>

namespace Engine
{
    PCPlatform::PCPlatform()
        : window(nullptr)
    {
    }

    bool PCPlatform::Init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            return false;
        }

        window = SDL_CreateWindow("My Engine Window",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (!window)
        {
            std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            window = nullptr;
            return false;
        }

        Sprite::SetRenderer(renderer);

        return true;
    }

    // ----------------------------------------------------
    void PCPlatform::ClearScreen()
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);
    }

    // ----------------------------------------------------
    void PCPlatform::DrawText(const std::string&, int, int)
    {
        // Not implemented yet.
    }

    // ----------------------------------------------------
    void PCPlatform::DrawSprite(int x, int y, Sprite& sprite)
    {
        SDL_Rect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = sprite.GetWidth();
        destRect.h = sprite.GetHeight();

        SDL_RenderCopy(renderer, sprite.GetTexture(), nullptr, &destRect);
    }

    // ----------------------------------------------------
    void PCPlatform::Present()
    {
        SDL_RenderPresent(renderer);
    }

    // ----------------------------------------------------
    void PCPlatform::Delay(int ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    // ----------------------------------------------------
    void PCPlatform::FreeResources()
    {
        if (renderer)
        {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }

        if (window)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }

        SDL_Quit();
    }

} // namespace Engine