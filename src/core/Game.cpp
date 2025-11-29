#include <iostream>

#include "core/Sprite.hpp"
#include "core/Game.hpp"

#include "generated/graphics/image.hpp"
#include "generated/palettes/image.hpp"

namespace Engine
{
    Game::Game(Platform& p)
        : platform(p)
    {
        // Constructor implementation can be empty or include initialization logic
    }

    void Game::Run()
    {
        if (!platform.Init())
            return; // Initialization failed, exit the game loop
        
        Sprite sprite(image_image, image_palette);

        while (frameCounter < 300)
        {
            platform.ClearScreen();

            platform.DrawSprite(10, 10, sprite); // Example usage of DrawSprite
            platform.DrawSprite(20, 20, sprite);

            platform.Present();

            platform.Delay(16); // ~60 FPS
            frameCounter++;
        }

        platform.FreeResources();
    }
} // namespace Engine