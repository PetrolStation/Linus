#pragma once

#include <Core/Window/Window.h>
#include <fstream>

namespace PetrolEngine{
    class Linus : public WindowApi {
    public:
        std::vector<char> buffer;
        std::ifstream mouseFile;

        void clear();
        void swapBuffers() override;

        void showCursor(bool show   ) override {};
        void setVSync  (bool enabled) override {};
        void setIcon   (Image* image) override {};
        void pollEvents(            ) override;
        void close     (            ) override {};

        int init() override { return 0; };

        bool shouldClose() override { return false; };
        bool isPressed(Keys key) override { return false; };

        void createWindowSurface(void* instance, const void* allocation, void* surface) override {};

        Linus(int width, int height, std::string title);
        ~Linus() override;
    };
}
