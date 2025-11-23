/**
 * @file Palette.hpp
 * @brief Definition of the Palette struct for color palettes.
 *
 * This file defines the Palette struct used to represent color palettes
 * in indexed images within the engine.
 */
#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <cstdint>

namespace Engine
{
    /**
     * @struct Palette
     * @brief The Palette struct represents a color palette used for indexed images.
     *
     * This struct contains an array of colors and the size of the palette.
     */
    struct Palette
    {
        const uint32_t * colors;    ///< Pointer to the array of colors in the palette.
        unsigned int    size;       ///< Number of colors in the palette.
    };
}

#endif // PALETTE_HPP