#include <string>
#include <sstream>
#include <fstream>

#include "Shader.h"
#include "OpenGLUtil.h"
#include "Resources.h"

using std::ifstream;
using std::stringstream;

Shader::Shader(const string& filePath)
    : filePath(filePath), rendererId(0) {

    ShaderProgramSource source = parseShader(filePath);

    printf("\n\n");
    printf("VERTEX PROGRAM LOADED:\n%s\n", source.vertexSource.c_str());
    printf("FRAGMENT PROGRAM LOADED:\n%s\n", source.fragmentSource.c_str());

    rendererId = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(rendererId));
}


void Shader::bind() const {
    GLCall(glUseProgram(rendererId));
}

void Shader::unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const string& name, float x, float y, float z, float w) {
    GLCall(int id = glGetUniformLocation(rendererId, name.c_str()));
    GLCall(glUniform4f(id, x, y, z, w));
}

void Shader::setUniform1i(const string& name, int x) {
    GLCall(int id = glGetUniformLocation(rendererId, name.c_str()));
    GLCall(glUniform1i(id, x));
}

ShaderProgramSource Shader::parseShader(const string& filePath) {
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    const string& resourcesFilePath = Resources::getAbsoluteResourcesPath(filePath);
    printf("Parsing shader from %s\n", resourcesFilePath.c_str());

    //NOTE: Already opens the file:
    ifstream stream(resourcesFilePath);

    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != string::npos) {
            if (line.find("vertex") != string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != string::npos)
                type = ShaderType::FRAGMENT;
        } else {
            ss[(int) type] << line << "\n";
        }
    }

    return {
        ss[(int) ShaderType::VERTEX].str(),
        ss[(int) ShaderType::FRAGMENT].str()
    };
}

unsigned int Shader::compileShader(unsigned int type, const string& source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, NULL));
    GLCall(glCompileShader(id));

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = new char[length]; //(char*) alloca(length * sizeof(char)); //NOTE: Allocated dynamically on the stack!
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        fprintf(stderr, "%s\n%s\n", "Failed to compile a shader!", message);

        GLCall(glDeleteShader(id));
        return 0;
    }
    return id;
}

unsigned int Shader::createShader(const string& vertexShader, const string& fragmentShader) {
    unsigned int programId = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    GLCall(glAttachShader(programId, vs));
    GLCall(glAttachShader(programId, fs));
    GLCall(glLinkProgram(programId));
    GLCall(glValidateProgram(programId));

    GLCall(glDetachShader(programId, vs));
    GLCall(glDetachShader(programId, fs));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    return programId;
}
