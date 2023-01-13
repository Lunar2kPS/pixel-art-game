#pragma once

#include <string>
#include "glm/glm.hpp"

using namespace glm;
using std::string;

struct ShaderProgramSource {
    string vertexSource;
    string fragmentSource;
};

class Shader {
    private:
        const string& filePath;
        unsigned int rendererId;

    public:
        Shader(const string& filePath);
        ~Shader();
        void bind() const;
        void unbind() const;
        void setUniform1i(const string& name, int x);
        void setUniform4f(const string& name, float x, float y, float z, float w);
        void setUniformMatrix4fv(const string& name, mat4& matrix);

    private:
        unsigned int getUniformId(const string& name);
        ShaderProgramSource parseShader(const string& filePath);
        unsigned int compileShader(unsigned int type, const string& source);
        unsigned int createShader(const string& vertexShader, const string& fragmentShader);
};
