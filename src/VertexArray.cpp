#include <vector>

#include "VertexArray.h"
#include "OpenGLUtil.h"

using std::vector;

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &rendererId));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &rendererId));
}

void VertexArray::bind() const {
    //NOTE: Also binds the vertex buffer linked to it!
    GLCall(glBindVertexArray(rendererId));
}

void VertexArray::unbind() const {
    GLCall(glBindVertexArray(rendererId));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();
    vector<VertexAttribute> attributes = layout.getAttributes();
    unsigned int offset = 0;
    for (int i = 0; i < attributes.size(); i++) {
        VertexAttribute attribute = attributes[i];
        GLCall(glEnableVertexAttribArray(i));
        
        //NOTE: THIS BINDS the currently-bound vertex buffer to the currently-bound vao! (vertex buffer to vertex array obj)
        GLCall(glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalized, layout.getStride(), (const void*) offset));
        offset += attribute.count * VertexAttribute::getSizeOfType(attribute.type);
    }
}
