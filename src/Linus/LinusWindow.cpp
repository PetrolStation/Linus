//
// Created by samuel on 12/25/22.
//

#include "Linus.h"
#include "Static/Window/Window.h"
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
 #include <unistd.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <glad/glad.h>
#include <Static/Renderer/Renderer.h>
namespace PetrolEngine{
    void Linus::clear() {
        buffer.clear();
    }

    void setColor(uint8 red, uint8 green, uint8 blue){
        std::cout << "\033[38;2;" << (int)red << ";" << (int)green << ";" << (int)blue << "m";
    }
    
    void Linus::swapBuffers() {
        auto& width  = this->windowData.width;
        auto& height = this->windowData.height;
        uint8* buffer = new uint8[width * height * 3];
        glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
        
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                int base = (y * width * 3) + (x * 3);
                setColor(buffer[base+0], buffer[base+1], buffer[base+2]);
                std::cout<<"█";
            }
            std::cout<<"\n";
        }
        
    }

    void Linus::pollEvents(){  
        char data[3];
        
        if(!this->mouseFile.read(data, sizeof(data))) return;

        int button = data[0] & 0x07;

        cursorXPos += data[1];
        cursorYPos += data[2];

        if(cursorXPos < 0) cursorXPos = 0;
        if(cursorYPos < 0) cursorYPos = 0;
    }

    Linus::Linus(int width, int height, std::string title) {
        this->windowData = {width, height, ""};
        this->buffer.resize(width * height);
        this->mouseFile.open("/dev/input/mice", std::ios::in | std::ios::binary);
        //this->miceHandle = open("/dev/input/mice", O_RDONLY);
        //Renderer::createGraphicsContext()->init();

    }

    Linus::~Linus(){
        this->mouseFile.close();
        //close(this->miceHandle);
    }
}
