#pragma once

#include <string>
#include "OpenGLUtil.h"

using std::string;

class Texture {
    private:
        unsigned int rendererId;
        string filePath;
        unsigned char* localBuffer;
        int width;
        int height;
        int bpp;

    public:
        Texture(const string& filePath);
        ~Texture();

        inline int getWidth() const { return width; }
        inline int getHeight() const { return height; }

        void bind(unsigned int slot = 0) const;
        void unbind() const;
};
