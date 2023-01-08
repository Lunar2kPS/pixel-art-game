#include "Renderer.h"
#include "OpenGLUtil.h"

void Renderer::clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& vao, const IndexBuffer& ib, const Shader& shader) const {
    shader.bind();
    vao.bind();
    ib.bind();

    //Draw call!
    //NOTE: Requires an index buffer (GL_ELEMENT_ARRAY_BUFFER),
    //  and NULL indicates OpenGL should use the already-bound index buffer.
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, NULL));
}
