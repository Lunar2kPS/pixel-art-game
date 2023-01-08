#pragma once

#include <vector>
#include "OpenGLUtil.h"

using std::vector;

struct VertexAttribute {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }

        //TODO: More informative error?
        //ASSERT(false);
        throw 100;
        return 0;
    }
};

class VertexBufferLayout {
    private:
        unsigned int stride;
        vector<VertexAttribute> attributes;
    public:
        VertexBufferLayout()
            : stride(0) { }
    
        inline unsigned int getStride() const { return stride; }
        inline const vector<VertexAttribute>& getAttributes() const { return attributes; }

        template<typename T> void push(unsigned int count) {
            //TODO: More informative error?
            //ASSERT(false);
            //static_assert(false);
            throw 200;
        }
        
        template<> void push<float>(unsigned int count);
        template<> void push<unsigned int>(unsigned int count);
        template<> void push<unsigned char>(unsigned int count);
};
