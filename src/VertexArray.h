#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
    private:
        unsigned int rendererId;
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void unbind() const;
        void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};