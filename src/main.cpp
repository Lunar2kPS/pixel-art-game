#include <stdio.h>
#include <thread>
#include <sstream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "GameVersion.h"
#include "platforms.h"

using namespace std;

static bool glfwInitialized = 0;

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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        //NOTE: BEFORE doing this, I was getting the following results:
        //  Windows:        OpenGL 4.6          ==> NOW OpenGL 3.2
        //  MacOS:          OpenGL 2.1          ==> NOW OpenGL 4.1!
        //  Linux:          OpenGL 4.6          ==> NOW OpenGL 3.2
        //So, we set it to use OpenGL Core profile with forward compatibility: 
        glfwWindowHint(GLFW_OPENGL_PROFILE,             GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,      GL_TRUE);

        glfwSetErrorCallback(errorCallback);
    }

    GLFWwindow* windowPtr = glfwCreateWindow(width, height, title, NULL, NULL);
    window = windowPtr;
    if (windowPtr == NULL) {
        fprintf(stderr, "Failed to create window or OpenGL context!\n");
        glfwTerminate();
        return 2;
    }

    if (!glfwInitialized) {
        glfwMakeContextCurrent(windowPtr);
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

const char* getPlatformName() {
    return 
#if defined WINDOWS
        "Windows"
#elif defined MACOS
        "MacOS"
#elif defined LINUX
        "Linux"
#else
        "UNKNOWN"
#endif
    ;
}

int main() {
    printf(PROJECT_NAME " v" PROJECT_VERSION "\n");

    GLFWwindow* window;
    int initError = tryCreateWindow("Pixel Art Game", 800, 600, window);
    if (initError != 0) {
        fprintf(stderr, "%s%d", "Exiting with initialization exit code ", initError);
        return initError;
    }

    printf("%s%s\n", "Platform: ", getPlatformName());
    printf("\n");

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
