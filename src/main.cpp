#include <stdio.h>
#include <thread>
#include <sstream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "GameVersion.h"

using namespace std;

void errorCallback(int errorCode, const char* description) {
    stringstream ss;
    ss << "Error code: " << errorCode << "\n";
    ss << description;
    ss << "\n";

    const char* message = ss.str().c_str();
    fprintf(stderr, message);
}

int main() {
    printf(PROJECT_NAME " v" PROJECT_VERSION "\n");

    if (glfwInit() == GLFW_FALSE) {
        fprintf(stderr, "GLFW initialization failed!\n");
        return 1;
    }

    glfwSetErrorCallback(errorCallback);

    //NOTE: Let's require a certain (old) version of OpenGL or newer...
    //Like OpenGL 3.0+:
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); //NOTE: Context profiles are only available in OpenGL 3.2+, so we'll require that!

    //NOTE: BEFORE doing this, I was getting the following results:
    //  Windows:        OpenGL 4.6          ==> NOW OpenGL 3.2
    //  MacOS:          OpenGL 2.1          ==> NOW OpenGL 4.1!
    //  Linux:          OpenGL 4.6          ==> NOW OpenGL 3.2
    //So, we set it to use OpenGL Core profile with forward compatibility: 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "TEST WINDOW", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create window or OpenGL context!\n");
        //TODO: try-finally-like handling from C#.. I wonder how to do that here:
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context with GLAD!\n");
        return 3;
    }
    printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    while (!glfwWindowShouldClose(window)) {
        //NOTE: Now that we have modern OpenGL loaded from glad (the library),
        //We can use GL calls!
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f,  0.0f);
        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    printf("Done!\n");

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
