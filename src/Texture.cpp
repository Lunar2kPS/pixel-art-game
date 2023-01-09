#include "Texture.h"
#include "libraries/stb_image.h"

Texture::Texture(const string& filePath)
    : filePath(filePath), localBuffer(NULL), width(0), height(0), bpp(0) {
    //NOTE: PNG files are stored from top of the image.
    //OpenGL starts from the bottom of textures as y = 0.
    stbi_set_flip_vertically_on_load(true);

    //NOTE: 4 channels for RGBA
    localBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);

    GLCall(glGenTextures(1, &rendererId));
    bind();

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
    unbind();

    if (localBuffer != NULL)
        stbi_image_free(localBuffer);
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &rendererId));
}

void Texture::bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));
}

void Texture::unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}