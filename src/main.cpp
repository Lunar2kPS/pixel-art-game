#include <stdio.h>
#include <thread>
#include <sstream>
#include <fstream>
#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "GameVersion.h"
#include "platforms.h"

using namespace std;

static bool glfwInitialized = 0;
static string resourcesFolder;

void errorCallback(int errorCode, const char* description) {
    stringstream ss;
    ss << "GLFW Error code: " << errorCode << "\n";
    ss << description;
    ss << "\n";

    const char* message = ss.str().c_str();
    fprintf(stderr, "%s", message);
}

int tryCreateWindow(const char* title, int width, int height, GLFWwindow*& window) {
    if (!glfwInitialized) {
        if (!glfwInit()) {
            fprintf(stderr, "GLFW initialization failed!\n");
            return 1;
        }

        //NOTE: Let's require a certain (old) version of OpenGL or newer...
        //Like OpenGL 3.0+. HOWEVER,
        //NOTE: Context profiles are only available in OpenGL 3.2+, so we'll require that!
        //TODO: Try to require 4.6, then if we get the error (during callback) of "Requested OpenGL version 4.6, got version 4.1", then request that version instead!
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        //NOTE: BEFORE doing this, I was getting the following results:
        //  Windows:        OpenGL 4.6          ==> NOW OpenGL 3.2
        //  MacOS:          OpenGL 2.1          ==> NOW OpenGL 4.1!
        //  Linux:          OpenGL 4.6          ==> NOW OpenGL 3.2
        //So, we set it to use OpenGL Core profile with forward compatibility: 
        glfwWindowHint(GLFW_OPENGL_PROFILE,             GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,      GL_TRUE);

        glfwSetErrorCallback(errorCallback);
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create window or OpenGL context!\n");
        glfwTerminate();
        return 2;
    }

    if (!glfwInitialized) {
        glfwMakeContextCurrent(window);
        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            printf("Failed to initialize OpenGL context with GLAD!\n");
            return 3;
        }
        printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    }
    glfwInitialized = true;
    return 0;
}

struct ShaderProgramSource {
    string vertexSource;
    string fragmentSource;
};

ShaderProgramSource parseShader(const string& filePath) {
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    string resourcesFilePath = filePath;
    if (resourcesFilePath.find(resourcesFolder) == string::npos)
        resourcesFilePath = resourcesFolder + "/" + resourcesFilePath;
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

unsigned int compileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length]; //(char*) alloca(length * sizeof(char)); //NOTE: Allocated dynamically on the stack!
        glGetShaderInfoLog(id, length, &length, message);
        fprintf(stderr, "%s\n%s\n", "Failed to compile a shader!", message);

        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int createShader(const string& vertexShader, const string& fragmentShader) {
    unsigned int programId = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(programId, vs);
    glAttachShader(programId, fs);
    glLinkProgram(programId);
    glValidateProgram(programId);

    glDetachShader(programId, vs);
    glDetachShader(programId, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return programId;
}

void replaceAll(string& source, const string& from, const string& to) {
    string newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    size_t lastPos = 0;
    size_t findPos;

    while((findPos = source.find(from, lastPos)) != string::npos) {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString.append(source, lastPos, source.length() - lastPos);
    source.swap(newString);
}

int main(int argCount, char* args[]) {    
    printf(PROJECT_NAME " v" PROJECT_VERSION "\n");

    GLFWwindow* window;
    int initError = tryCreateWindow("Pixel Art Game", 800, 600, window);
    if (initError != 0) {
        fprintf(stderr, "%s%d\n", "Exiting with initialization exit code ", initError);
        return initError;
    }

    printf("%s%s\n", "Platform: ", getPlatformName());
    printf("\n");

    const int VERTEX_COUNT = 6;
    const int POSITION_COUNT = 2 * VERTEX_COUNT;
    float r = 0.5f;
    float s = 0.01f;
    float positions[POSITION_COUNT] = {
        //{0, 1, 2}
        -r, -r,
        -r,  r,
         r, -r,

        //{3, 2, 1}
         r,  r,
         r, -r,
        -r,  r
    };

    for (int i = 0; i < POSITION_COUNT / 2; i++)
        positions[i] -= s;
    for (int i = POSITION_COUNT / 2; i < POSITION_COUNT; i++)
        positions[i] += s;

    unsigned int vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    unsigned int vertexBufferId;
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), 0);

    string exeFilePath = args[0];
    replaceAll(exeFilePath, "\\", "/");
    size_t indexOfLastFolderSeparator = exeFilePath.find_last_of("/");
    
    resourcesFolder = exeFilePath.substr(0, indexOfLastFolderSeparator);
    printf("Resources folder path = %s\n", resourcesFolder.c_str());

    ShaderProgramSource source = parseShader("resources/shaders/Basic.glsl");
    printf("VERTEX PROGRAM LOADED:\n%s\n\n", source.vertexSource.c_str());
    printf("FRAGMENT PROGRAM LOADED:\n%s\n\n", source.fragmentSource.c_str());

    unsigned int shaderId = createShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shaderId);

    while (!glfwWindowShouldClose(window)) {
        //NOTE: Now that we have modern OpenGL loaded from glad (the library),
        //We can use GL calls!
        glClear(GL_COLOR_BUFFER_BIT);

        //NOTE: No index buffer!
        glDrawArrays(GL_TRIANGLES, 0, POSITION_COUNT / 2);

        //NOTE: WITH an index buffer!
        // glDrawElements(GL_TRIANGLES, POSITION_COUNT / 2, , NULL);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    printf("Done!\n");

    glDeleteProgram(shaderId);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
