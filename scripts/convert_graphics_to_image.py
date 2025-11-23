import os
from PIL import Image

def convert_png_to_indexed(png_path, hpp_path):
    """
    Convert a PNG image to an indexed format and generates a .hpp file.
    Then generates a .hpp file containing:
      - array of indexed pixels (uint8_t)
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
        # Transparency is not provided by palette[], it is deduced from the original image
        # by looking for a pixel with the same index in indexed_img:
        # For simplicity, set alpha = 255 for all.
        a = 255
        pal_rgba.append((r, g, b, a))

    # Generation of the .hpp
    with open(hpp_path, "w") as f:
        f.write(f"#ifndef GENERATED_GRAPHICS_{name.upper()}_IMAGE_HPP\n")
        f.write(f"#define GENERATED_GRAPHICS_{name.upper()}_IMAGE_HPP\n\n")
        f.write("// This file is auto-generated. Do not edit manually.\n")
        f.write(f"// Original image: {os.path.basename(png_path)}\n\n")
        f.write("#include <cstdint>\n")
        f.write("#include \"../../core/Image.hpp\"\n\n")

        f.write("using namespace Engine;\n\n")

        # Indexed pixels
        f.write(f"extern uint8_t {name}_pixels[{w*h}];\n\n")
        # Image struct
        f.write(f"extern Image {name}_image;\n\n")

        f.write(f"#endif // GENERATED_GRAPHICS_{name.upper()}_IMAGE_HPP\n")
    
    # Generation of the .cpp
    cpp_path = hpp_path.replace(".hpp", ".cpp")
    with open(cpp_path, "w") as f:
        f.write(f"#include \"{os.path.basename(hpp_path)}\"\n\n")

        # Indexed pixels
        f.write(f"uint8_t {name}_pixels[{w*h}] = {{\n")
        for i, p in enumerate(pixels):
            if i % w == 0:
                f.write("    ")
            f.write(f"{p:3d}, ")
            if (i + 1) % w == 0:
                f.write("\n")
        f.write("};\n\n")

        # Image struct
        f.write(f"Image {name}_image = {{\n")
        f.write(f"    .pixels = {name}_pixels,\n")
        f.write(f"    .width = {w},\n")
        f.write(f"    .height = {h},\n")
        f.write(f"    .paletteSize = {palette_size},\n")
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

    parser = argparse.ArgumentParser(description="Convert PNGs to indexed .hpp.")
    parser.add_argument("input_file", help="PNG file to convert")
    parser.add_argument("output_file", help="Output file path for the generated .hpp")

    args = parser.parse_args()

    convert_png_to_indexed(args.input_file, args.output_file)