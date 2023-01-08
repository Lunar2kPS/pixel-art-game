#pragma once

#include <string>

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
        void setUniform4f(const string& name, float x, float y, float z, float w);

    private:
        unsigned int getUniformId(const string& name);
        ShaderProgramSource parseShader(const string& filePath);
        unsigned int compileShader(unsigned int type, const string& source);
        unsigned int createShader(const string& vertexShader, const string& fragmentShader);
};
