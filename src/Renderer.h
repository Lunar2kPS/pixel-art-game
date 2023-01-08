#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer {
    public:
        void clear() const;
        void draw(const VertexArray& vao, const IndexBuffer& ib, const Shader& shader) const;
};
