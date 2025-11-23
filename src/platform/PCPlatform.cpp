#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "platform/PCPlatform.hpp"
#include "core/Sprite.hpp"

namespace Engine
{
    PCPlatform::PCPlatform()
    {
        // Constructor can be empty or include initialization logic if needed
    }

    bool PCPlatform::Init()
    {
        if (!glfwInit())
        {
            std::cerr << "[PC] GLFW initialization failed.\n";
            return false;
        }

        // OpenGL context settings (example: OpenGL 3.3 Core)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PC Platform Window", nullptr, nullptr);
        if (!window)
        {
            std::cerr << "[PC] Failed to create GLFW window.\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Equivalent to SDL_RENDERER_PRESENTVSYNC

        GLenum err = glewInit();
        if (err != GLEW_OK)
        {
            std::cerr << "[PC] GLEW initialization failed: " 
                    << glewGetErrorString(err) << "\n";
            glfwDestroyWindow(window);
            glfwTerminate();
            return false;
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        std::cout << "[PC] OpenGL initialization complete.\n";

        return true;
    }

    void PCPlatform::ClearScreen()
    {
        glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void PCPlatform::DrawText(const std::string& text, int x, int y)
    {
        std::cout << "Not possible yet on PC platform: " << text << " at (" << x << ", " << y << ")\n";
    }

    void PCPlatform::Present()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void PCPlatform::Delay(int ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    void PCPlatform::FreeResources()
    {
        if (window)
        {
            glfwDestroyWindow(window);
            window = nullptr;
        }

        glfwTerminate();
        std::cout << "[PC] Resources freed and GLFW terminated.\n";
    }

    void PCPlatform::DrawSprite(int x, int y, Engine::Sprite& sprite)
    {
        const uint8_t * pixelData   = sprite.GetPixelData();
        const uint32_t * palette    = sprite.GetPalette();
        int width                   = sprite.GetWidth();
        int height                  = sprite.GetHeight();

        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                uint8_t pixelIndex  = pixelData[j * width + i];
                uint32_t color      = palette[pixelIndex];

                if (color == 0x000000FF) // Assuming 0x000000FF is the transparent color
                    continue;

                float r = ((color >> 24) & 0xFF) / 255.0f;
                float g = ((color >> 16) & 0xFF) / 255.0f;
                float b = ((color >> 8) & 0xFF) / 255.0f;

                glColor3f(r, g, b);
                glBegin(GL_POINTS);
                glVertex2i(x + i, y + j);
                glEnd();
            }
        }
    }
} // namespace Engine