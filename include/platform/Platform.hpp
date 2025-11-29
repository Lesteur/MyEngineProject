/**
 * @file Platform.hpp
 * @brief The Platform interface defines the methods required for platform-specific operations.
 *
 * It serves as a base class for different platform implementations, allowing for
 * cross-platform compatibility.
 */
#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <string>

#include "core/Sprite.hpp"

namespace Engine
{
    /**
     * @class Platform
     * @brief The Platform class provides an interface for platform-specific operations.
     *
     * This class defines the methods that must be implemented by any platform-specific class,
     * such as initializing the platform, clearing the screen, drawing text, presenting the screen,
     * and introducing a delay.
     */
    class Platform
    {
        public:
            /**
             * @brief Default constructor for the Platform class.
             *
             * This constructor initializes the platform object.
             */
            virtual ~Platform() {}

            /**
             * @brief Initializes the platform.
             *
             * This method is used to perform any necessary initialization for the platform,
             * such as setting up graphics, input handling, etc.
             * @return true if initialization was successful, false otherwise.
             */
            virtual bool Init() = 0;

            /**
             * @brief Clears the screen.
             *
             * This method is used to clear the current screen, preparing it for new rendering.
             */
            virtual void ClearScreen() = 0;

            /**
             * @brief Draws text on the screen at the specified coordinates.
             *
             * This method is used to render the given text at the specified (x, y) position on the screen.
             * @param text The text to be drawn.
             * @param x The x-coordinate where the text should be drawn.
             * @param y The y-coordinate where the text should be drawn.
             */
            virtual void DrawText(const std::string& text, int x, int y) = 0;

            /**
             * @brief Presents the rendered content on the screen.
             *
             * This method is used to present the current frame to the display, making it visible to the user.
             */
            virtual void Present() = 0;

            /**
             * @brief Introduces a delay for the specified duration.
             *
             * This method is used to pause the execution for a given number of milliseconds.
             * @param ms The duration of the delay in milliseconds.
             */
            virtual void Delay(int ms) = 0;

            /**
             * @brief Draws a sprite on the screen at the specified coordinates.
             *
             * This method is used to render the given sprite at the specified (x, y) position on the screen.
             * @param x The x-coordinate where the sprite should be drawn.
             * @param y The y-coordinate where the sprite should be drawn.
             * @param sprite The sprite to be drawn.
             */
            virtual void DrawSprite(int x, int y, Engine::Sprite& sprite) = 0;

            /**
             * @brief Frees any resources allocated by the platform.
             *
             * This method is used to clean up and release any resources used by the platform.
             */
            virtual void FreeResources() = 0;
    };
} // namespace Engine

#endif // PLATFORM_HPP