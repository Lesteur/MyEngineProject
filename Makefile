# ============================================================
# Makefile.pc — Build configuration for PC (Linux / Windows / macOS)
# ============================================================

# Project settings
PROJECT		:=	project_pc.exe
PLATFORM	:=	pc
BUILD_DIR	:=	build/$(PLATFORM)
SRC_DIR		:=	src
INC_DIR		:=	include
DATA_DIR	:=	data
GEN_DIR		:=	$(INC_DIR)/generated

# Compiler and flags
CXX			:=	g++
CXXFLAGS	:=	-std=c++17 -O2 -Wall -Wextra -Wpedantic \
				-I$(INC_DIR) -I$(GEN_DIR)/graphics -I$(GEN_DIR)/palettes

# Linker flags
LDFLAGS		:=	`sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_net -lSDL2_gfx -lm

# Data files
GRAPHICS	:=	$(wildcard $(DATA_DIR)/graphics/*.png)

# Source files (recursive search)
SRC			:=	$(wildcard $(SRC_DIR)/core/*.cpp) $(SRC_DIR)/main_pc.cpp $(SRC_DIR)/platform/PCPlatform.cpp
OBJ			:=	$(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

GRAPHICS_SRC:=	$(GRAPHICS:$(DATA_DIR)/graphics/%.png=$(GEN_DIR)/graphics/%.cpp)
GRAPHICS_INC:=	$(GRAPHICS:$(DATA_DIR)/graphics/%.png=$(GEN_DIR)/graphics/%.hpp)
GRAPHICS_OBJ:=	$(GRAPHICS:$(DATA_DIR)/graphics/%.png=$(BUILD_DIR)/generated/graphics/%.o)

PALETTES_SRC:=	$(GRAPHICS:$(DATA_DIR)/graphics/%.png=$(GEN_DIR)/palettes/%.cpp)
PALETTES_INC:=	$(GRAPHICS:$(DATA_DIR)/graphics/%.png=$(GEN_DIR)/palettes/%.hpp)
PALETTES_OBJ:=	$(GRAPHICS:$(DATA_DIR)/graphics/%.png=$(BUILD_DIR)/generated/palettes/%.o)

# Output binary
TARGET		:= $(BUILD_DIR)/$(PROJECT)

# ============================================================

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJ) $(GRAPHICS_OBJ) $(PALETTES_OBJ)
	@mkdir -p $(dir $@)
	@echo "Linking $(PROJECT) for $(PLATFORM)..."
	$(CXX) $(OBJ) $(GRAPHICS_OBJ) $(PALETTES_OBJ) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

# Compile step
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(PALETTES_INC) $(GRAPHICS_INC)
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/generated/graphics/%.o: $(GEN_DIR)/graphics/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling generated graphics source $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/generated/palettes/%.o: $(GEN_DIR)/palettes/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling generated palettes source $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Graphics generation step

# Generate the graphics source and header
$(GEN_DIR)/graphics/%.hpp: $(DATA_DIR)/graphics/%.png
	@mkdir -p $(dir $@)
	@echo "Generating graphics source for $<"
	python3 scripts/convert_graphics_to_image.py $< $@

$(GEN_DIR)/graphics/%.cpp: $(GEN_DIR)/graphics/%.hpp
	@true

# Generate the palettes source and header
$(GEN_DIR)/palettes/%.hpp: $(DATA_DIR)/graphics/%.png
	@mkdir -p $(dir $@)
	@echo "Generating palettes source for $<"
	python3 scripts/convert_graphics_to_palette.py $< $@

$(GEN_DIR)/palettes/%.cpp: $(GEN_DIR)/palettes/%.hpp
	@true

# Graphics target
graphics: $(GRAPHICS_INC) $(GRAPHICS_SRC) $(PALETTES_INC) $(PALETTES_SRC)

# Run target
run: $(TARGET)
	@echo "Running $(PROJECT)..."
	./$(TARGET)

# Clean target
clean:
	@echo "Cleaning build directory for $(PLATFORM)..."
	rm -rf $(BUILD_DIR)
	rm -rf $(GEN_DIR)

.PHONY: all clean run