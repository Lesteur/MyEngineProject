/**
 * @file Sprite.hpp
 * @brief The Sprite class converts indexed images into OpenGL textures for 2D rendering.
 */

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "core/Image.hpp"
#include "core/Palette.hpp"

#include <SDL2/SDL.h>

namespace Engine
{
    /**
     * @class Sprite
     * @brief Wraps an indexed image and converts it to an OpenGL texture.
     */
    class Sprite
    {
    private:
        SDL_Texture * texture;///< SDL texture.
        int width;            ///< Sprite width in pixels.
        int height;           ///< Sprite height in pixels.

        static SDL_Renderer * renderer; ///< SDL renderer for texture creation.

    public:
        /**
         * @brief Creates a sprite from an indexed image and its palette.
         * @param img Indexed image.
         * @param pal Color palette.
         */
        Sprite(const Image& img, const Palette& pal);

        /**
         * @brief Frees the texture resource.
         */
        ~Sprite();

        /**
         * @brief Returns the texture ID.
         */
        SDL_Texture * GetTexture() const;

        /**
         * @brief Returns the sprite width.
         */
        int GetWidth() const;

        /**
         * @brief Returns the sprite height.
         */
        int GetHeight() const;

        /**
         * @brief Sets the SDL renderer for texture creation.
         * @param rend Pointer to the SDL renderer.
         */
        static void SetRenderer(SDL_Renderer * rend)
        {
            renderer = rend;
        }
    };
}

#endif // SPRITE_HPP