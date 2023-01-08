#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "GameVersion.h"
#include "platforms.h"

#include "IndexBuffer.h"
#include "OpenGLUtil.h"
#include "Resources.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

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

    {
        Resources::initialize(args[0]);

        const int VERTEX_COUNT = 4;
        const int POSITION_COUNT = 2 * VERTEX_COUNT;
        const int INDEX_COUNT = 6;
        float r = 0.5f;

        //Triangle layout:
        //  1-----3
        //  | \   |
        //  |   \ |
        //  0-----2
        
        float positions[POSITION_COUNT] = {
            -r, -r,
            -r,  r,
            r, -r,
            r,  r,
        };

        unsigned int indices[INDEX_COUNT] = {
            0, 1, 2,
            3, 2, 1
        };

        VertexArray vao;
        VertexBuffer vb = VertexBuffer(positions, POSITION_COUNT * sizeof(float));
        IndexBuffer ib = IndexBuffer(indices, INDEX_COUNT);
        
        VertexBufferLayout layout;
        layout.push<float>(2);
        vao.addBuffer(vb, layout);

        Shader shader = Shader("resources/shaders/Basic.glsl");
        
        shader.bind();
        shader.setUniform4f("uniformColor", 0, 0.7f, 1, 1);

        //NOTE: VSYNC ON! Huge performance benefits..
        glfwSwapInterval(1);

        //CLEAR STATE
        shader.unbind();
        vao.unbind();
        vb.unbind();
        ib.unbind();

        float uniformColor[4] = { 0, 0, 1, 1 };
        double prevTime = glfwGetTime();
        while (!glfwWindowShouldClose(window)) {
            double time = glfwGetTime();
            double dt = time - prevTime;

            uniformColor[0] = 0.5f * cos(time) + 0.5f;
            uniformColor[1] = 0.5f * sin(time) + 0.5f;
            shader.bind();
            shader.setUniform4f("uniformColor", uniformColor[0], uniformColor[1], uniformColor[2], uniformColor[3]);
            
            ib.bind();

            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            GLCall(glDrawElements(GL_TRIANGLES, INDEX_COUNT, GL_UNSIGNED_INT, NULL));

            glfwSwapBuffers(window);
            glfwPollEvents();
            prevTime = time;
        }
        printf("Done!\n");
    } //Delete our stack-allocated data BEFORE terminating GLFW/OpenGL context, so everything we were using is cleaned up first.

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
