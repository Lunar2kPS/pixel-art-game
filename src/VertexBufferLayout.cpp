#include "VertexBufferLayout.h"
#include "OpenGLUtil.h"

// template<> void VertexBufferLayout::push<float>(unsigned int count) {
void VertexBufferLayout::pushFloat(unsigned int count) {
    VertexAttribute attribute = {
        GL_FLOAT,
        count,
        false
    };
    attributes.push_back(attribute);
    stride += count * VertexAttribute::getSizeOfType(GL_FLOAT);
}

// template<> void VertexBufferLayout::push<unsigned int>(unsigned int count) {
void VertexBufferLayout::pushUInt(unsigned int count) {    
    VertexAttribute attribute = {
        GL_UNSIGNED_INT,
        count,
        false
    };
    attributes.push_back(attribute);
    stride += count * VertexAttribute::getSizeOfType(GL_UNSIGNED_INT);
}

// template<> void VertexBufferLayout::push<unsigned char>(unsigned int count) {
void VertexBufferLayout::pushUChar(unsigned int count) {
    VertexAttribute attribute = {
        GL_UNSIGNED_BYTE,
        count,
        true
    };
    attributes.push_back(attribute);
    stride += count * VertexAttribute::getSizeOfType(GL_UNSIGNED_BYTE);
}
