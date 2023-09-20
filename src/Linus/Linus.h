#pragma once

#include "Core/Window/WindowResourceCreator.h"
#include "LinusWindow.h"

namespace PetrolEngine {
    class Linus_: public WindowResourceCreator {
    public:
        WindowApi* newWindow(int width, int height, const String& title) override { return new Linus(width, height, title); }
    };

    extern Linus_ Linus;
}
