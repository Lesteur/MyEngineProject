/**
 * @file Sprite.hpp
 * @brief The Sprite class represents a 2D image or animation in the game.
 *
 * This file contains the declaration of the Sprite class, which is used to manage
 * and render 2D images or animations within the game.
 */
#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <cstdint>

#include "core/Image.hpp"
#include "core/Palette.hpp"

namespace Engine
{
    /**
     * @class Sprite
     * @brief The Sprite class represents a 2D image or animation in the game.
     *
     * This class provides methods to load, manage, and render 2D images or animations.
     */
    class Sprite
    {
        private:
            // Private member variables for sprite properties (e.g., texture ID, position, size)
            Image image;        ///< Image data of the sprite.
            Palette palette;    ///< Color palette of the sprite.

        public:
            /**
             * @brief Constructs a Sprite object with the specified properties.
             * @param img The image data for the sprite.
             * @param pal The color palette for the sprite.
             */
            Sprite(Image img, Palette pal);

            /**
             * @brief Gets the width of the sprite.
             * @return The width of the sprite in pixels.
             */
            int GetWidth() const;

            /**
             * @brief Gets the height of the sprite.
             * @return The height of the sprite in pixels.
             */
            int GetHeight() const;

            /**
             * @brief Gets the pixel data of the sprite.
             * @return Pointer to the pixel data of the sprite.
             */
            const uint8_t * GetPixelData() const;

            /**
             * @brief Gets the color palette of the sprite.
             * @return Pointer to the color palette of the sprite.
             */
            const uint32_t * GetPalette() const;
    };
} // namespace Engine

#endif // SPRITE_HPP