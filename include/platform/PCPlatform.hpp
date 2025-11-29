/**
 * @file PCPlatform.hpp
 * @brief The PCPlatform class provides a platform-specific implementation for PC systems.
 *
 * This class inherits from the Platform interface and implements methods for initializing
 * the platform, clearing the screen, drawing text, presenting rendered content, and introducing delays.
 */
#ifndef PCPLATFORM_HPP
#define PCPLATFORM_HPP

#include "platform/Platform.hpp"

#include <SDL2/SDL.h>

namespace Engine
{
    /**
     * @class PCPlatform
     * @brief The PCPlatform class implements the Platform interface for PC systems.
     *
     * This class provides methods to initialize the platform, clear the screen, draw text,
     * present the rendered content, and introduce a delay specific to PC systems.
     */
    class PCPlatform : public Platform
    {
        protected:
            // PC-specific members can be added here
            static const int SCREEN_WIDTH = 240 * 4;  ///< Width of the screen in pixels.
            static const int SCREEN_HEIGHT = 160 * 4; ///< Height of the screen in pixels.
        
        private:
            SDL_Window * window = nullptr;    ///< Pointer to the SDL window.
            SDL_Renderer * renderer = nullptr;///< Pointer to the SDL renderer.

        public:
            /**
             * @brief Default constructor for the PCPlatform class.
             *
             * This constructor initializes the PC platform object.
             */
            PCPlatform();

            /**
             * @brief Destructor for the PCPlatform class.
             *
             * This destructor cleans up any resources used by the PC platform.
             * @return true if initialization was successful, false otherwise.
             */
            bool Init() override;

            /**
             * @brief Clears the screen.
             *
             * This method clears the current screen, preparing it for new rendering.
             */
            void ClearScreen() override;

            /**
             * @brief Draws text on the screen at the specified coordinates.
             *
             * This method renders the given text at the specified (x, y) position on the screen.
             * @param text The text to be drawn.
             * @param x The x-coordinate where the text should be drawn.
             * @param y The y-coordinate where the text should be drawn.
             */
            void DrawText(const std::string& text, int x, int y) override; // Ignore this for now

            /**
             * @brief Presents the rendered content on the screen.
             *
             * This method presents the current frame to the display, making it visible to the user.
             */
            void Present() override;

            /**
             * @brief Introduces a delay for the specified duration.
             *
             * This method pauses the execution for a given number of milliseconds.
             * @param ms The duration of the delay in milliseconds.
             */
            void Delay(int ms) override;

            /**
             * @brief Draws a sprite at the specified coordinates.
             *
             * This method renders the given sprite at the specified (x, y) position on the screen.
             * @param x The x-coordinate where the sprite should be drawn.
             * @param y The y-coordinate where the sprite should be drawn.
             * @param sprite The sprite to be drawn.
             */
            void DrawSprite(int x, int y, Sprite& sprite) override;

            /**
             * @brief Frees any resources allocated by the PC platform.
             *
             * This method cleans up and releases any resources used by the PC platform.
             */
            void FreeResources() override;
    };
} // namespace Engine

#endif // PCPLATFORM_HPP