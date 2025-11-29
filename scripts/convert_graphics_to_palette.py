import os
from PIL import Image

def convert_png_to_indexed(png_path, hpp_path):
    """
    Convert a PNG image to an indexed format and generates a .hpp file.
    Then generates a .hpp file containing:
      - array of the palette in RGBA (uint32_t)
    """
    name = os.path.splitext(os.path.basename(png_path))[0]

    # Open the image
    img = Image.open(png_path).convert("RGBA")
    w, h = img.size

    # Count unique colors (before quantization)
    colors = img.getcolors(maxcolors=1000000)
    if colors is None:
        raise ValueError(f"Image {png_path} has too many colors to be analyzed.")

    unique_count = len(colors)

    palette_size = unique_count
    quantize_colors = unique_count

    # Quantization of the image to indexed palette
    indexed_img = img.convert("P", palette=Image.ADAPTIVE, colors=quantize_colors)
    palette = indexed_img.getpalette()  # List R,G,B,... repeated 256 times
    pixels = list(indexed_img.getdata())

    # Reconstruction of the RGBA palette on palette_size values
    pal_rgba = []
    for i in range(palette_size):
        r = palette[i * 3 + 0]
        g = palette[i * 3 + 1]
        b = palette[i * 3 + 2]
        # Find alpha from original image
        a = 255
        for count, color in colors:
            if (color[0], color[1], color[2]) == (r, g, b):
                a = color[3]
                break
        pal_rgba.append((r, g, b, a))

    # Generation of the .hpp
    with open(hpp_path, "w") as f:
        f.write(f"#ifndef GENERATED_GRAPHICS_{name.upper()}_PALETTE_HPP\n")
        f.write(f"#define GENERATED_GRAPHICS_{name.upper()}_PALETTE_HPP\n\n")
        f.write("// This file is auto-generated. Do not edit manually.\n")
        f.write(f"// Original image: {os.path.basename(png_path)}\n\n")
        f.write("#include <cstdint>\n")
        f.write("#include \"../../core/Palette.hpp\"\n\n")

        f.write("using namespace Engine;\n\n")

        # Palette
        f.write(f"extern uint32_t {name}_pal[{palette_size}];\n\n")
        # Palette struct
        f.write(f"extern Palette {name}_palette;\n\n")

        f.write(f"#endif // GENERATED_GRAPHICS_{name.upper()}_PALETTE_HPP\n")

    # Generation of the .cpp
    cpp_path = hpp_path.replace(".hpp", ".cpp")

    with open(cpp_path, "w") as f:
        f.write(f"#include \"{os.path.basename(hpp_path)}\"\n\n")

        # Palette
        f.write(f"uint32_t {name}_pal[{palette_size}] = {{\n")
        for (r, g, b, a) in pal_rgba:
            rgba = (r << 24) | (g << 16) | (b << 8) | a
            f.write(f"    0x{rgba:08X},\n")
        f.write("};\n\n")

        # Palette struct
        f.write(f"Palette {name}_palette = {{\n")
        f.write(f"    .colors = {name}_pal,\n")
        f.write(f"    .size = {palette_size},\n")
        f.write("};\n\n")

    print(f"[OK] Converted: {png_path} → {hpp_path} and {cpp_path}")


def convert_folder(input_folder, output_folder):
    """
    Processes all PNGs in a folder and generates a .hpp file for each.
    """
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    for file in os.listdir(input_folder):
        if file.lower().endswith(".png"):
            png_path = os.path.join(input_folder, file)
            convert_png_to_indexed(png_path, output_folder)


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Convert PNGs to indexed palette.")
    parser.add_argument("input_file", help="PNG file to convert")
    parser.add_argument("output_file", help="Output file path for the generated .hpp")

    args = parser.parse_args()

    convert_png_to_indexed(args.input_file, args.output_file)