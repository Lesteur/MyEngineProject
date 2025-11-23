#include "core/Sprite.hpp"

namespace Engine
{
    Sprite::Sprite(Image img, Palette pal)
        : image(img), palette(pal)
    {
    }

    const uint8_t * Sprite::GetPixelData() const
    {
        return image.pixels;
    }

    const uint32_t * Sprite::GetPalette() const
    {
        return palette.colors;
    }

    int Sprite::GetWidth() const
    {
        return image.width;
    }

    int Sprite::GetHeight() const
    {
        return image.height;
    }
} // namespace Engine