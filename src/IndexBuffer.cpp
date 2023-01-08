#include "IndexBuffer.h"
#include "OpenGLUtil.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) {
    //TODO:
    // ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    this->count = count;

    GLCall(glGenBuffers(1, &rendererId));
    bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &rendererId));
}

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
}

void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
