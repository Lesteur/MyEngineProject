/**
 * @file Image.hpp
 * @brief The Image struct represents a 2D indexed image with a palette.
 *
 * This file contains the declaration of the Image struct, which is used to
 * manage indexed images within the engine.
 */
#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>

namespace Engine
{
    /**
     * @struct Image
     * @brief The Image struct represents a 2D indexed image with a palette.
     *
     * This struct contains pixel data, dimensions, and palette size for the image.
     */
    struct Image
    {
        const uint8_t * pixels;         ///< Pointer to the pixel data (indexed).
        unsigned int    width;          ///< Width of the image in pixels.
        unsigned int    height;         ///< Height of the image in pixels.
        unsigned int    paletteSize;    ///< Number of colors in the palette.
    };
}

#endif // IMAGE_HPP