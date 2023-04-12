//
// Created by samuel on 12/25/22.
//

#include "Linus.h"
#include "Static/Window/Window.h"
#include <cstdio>

namespace PetrolEngine{
    void Linus::clear() {
        buffer.clear();
    }

    void setColor(uint8 red, uint8 green, uint8 blue){
        auto print = [](int v){
            auto f = [](int c){ std::cout<<"\033["<<c<<"m"; };

            if(v & 0x8000) f( 0 );
            if(v & 0x0200) f( 60 * (v & 0x100) + 40 + ((clr & 0xE0) >> 5) );
            if(v & 0x0010) f( 60 * (v & 0x008) + 30 +  (clr & 0x07)       );
        }

        int bright = ( (red+green) + (blue+255) ) / 4;
        
        red    = red    / 128 * 0b10001;
        green  = green  / 128 * 0b10010;
        blue   = blue   / 128 * 0b10100;
        bright = bright / 128 * 0b11000;
        
        print((red+green) + (blue+bright));
    }
    
    void Linus::swapBuffers() {
        auto& width  = this->windowData.width;
        auto& height = this->windowData.height;
        GLubyte* buffer = new GLubyte[width * height * 3];
        glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
        
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                int base = (y * width * 3) + (x * 3);
                setColor(buffer[base+0], buffer[base+1], buffer[base+2]);
                //std::cout<<;
            }
            std::cout<<"\n";
        }
        std::cout<<std::endl;
    }

    void Linus::pollEvents(){
        if(fileHandle < 0) return;
        
        char data[3];
        
        ssize_t n = read(fileHandle, data, sizeof(data));

        if(n <= 0) return;

        int button = data[0] & 0x07;

        cursorXPos += stoi(data[1]);
        cursorYPos += stoi(data[2]);
    }

    Linus::Linus(uint width, uint height) {
        this->windowData = {width, height, ""};
        this->buffer.resize(width * height);
    }

    Linus::~Linus(){
        if(fileHandle >= 0) close(fileHandle);
    }
}
