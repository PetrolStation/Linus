#pragma once

#include <Core/Window/Window.h>


namespace PetrolEngine{
    class Linus : public WindowApi {
    public:
        std::vector<char> buffer;
        int miceHandle;

        void clear();
        void swapBuffers() override;

        void showCursor(bool show   ) override {};
        void setVSync  (bool enabled) override {};
        void setIcon   (Image* image) override {};
        void pollEvents(            ) override {};
        void close     (            ) override {};

        int init() override { return 0; };

        bool shouldClose() override { return false; };
        bool isPressed(Keys key) override { return false; };

        Linus(uint width, uint height);
        ~Linus() override = default;
    };
}
