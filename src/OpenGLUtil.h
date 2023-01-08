#pragma once

#include <stdio.h>
#include <glad/gl.h>

// #define ASSERT(x) if (!(x)) __debugbreak(); //TODO: Expand this to other compilers beyond just MSVC!
//TODO: Maybe use https://github.com/GPMueller/mwe-cpp-exception

#define GLCall(x) customGLClearErrors();\
    x;\
    customGLCheckForErrors(#x, __FILE__, __LINE__)

void customGLClearErrors();
bool customGLCheckForErrors(const char* functionName, const char* fileName, int lineNumber);