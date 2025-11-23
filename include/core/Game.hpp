/**
 * @file Game.hpp
 * @brief The Game interface defines the main game logic and manages the game loop.
 * 
 * This file contains the declaration of the Game class, which is used to run the game loop,
 */
#ifndef GAME_HPP
#define GAME_HPP

#include "platform/Platform.hpp"

namespace Engine
{
    /**
     * @class Game
     * @brief The Game class represents the main game logic and manages the game loop.
     * 
     * This class is responsible for initializing the platform, running the main game loop,
     * and handling rendering and input processing. It uses the Platform interface to perform
     * platform-specific operations such as drawing text and presenting the screen.
     */
    class Game
    {
        private:
            Platform&   platform;           ///< Reference to the platform used for rendering and input handling.
            int         frameCounter = 0;   ///< Counter for the number of frames rendered.

        public:
            /**
             * @brief Constructs a Game object with the specified platform.
             * @param p The platform to be used for rendering and input handling.
             */
            Game(Platform& p);

            /**
             * @brief Runs the main game loop.
             *
             * This method initializes the platform, enters the game loop, and handles rendering
             * and input processing. The loop continues until a termination condition is met.
             */
            void Run();
    };
} // namespace Engine

#endif // GAME_HPP