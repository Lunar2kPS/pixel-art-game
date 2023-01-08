#include "OpenGLUtil.h"

void customGLClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

bool customGLCheckForErrors(const char* functionName, const char* fileName, int lineNumber) {
    GLenum error;
    bool success = true;
    while ((error = glGetError()) != GL_NO_ERROR) {
        // printf("[OpenGL Error] (%d)\nCalled from %s in %s:%s", error, functionName, fileName, lineNumber);
        printf("[OpenGL Error] (%d): %s\nin %s:line %d\n\n", error, functionName, fileName, lineNumber);
        success = false;
    }
    return success;
}
