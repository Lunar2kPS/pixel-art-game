#include <stdio.h>
#include <thread>
#include <sstream>

#include <GLFW/glfw3.h>
#include "GameVersion.h"

using namespace std;

void errorCallback(int errorCode, const char* description) {
    stringstream ss;
    ss << "Error code: " << errorCode << "\n";
    ss << description;

    const char* message = ss.str().c_str();
    fprintf(stderr, message);
}

int main() {
    printf(PROJECT_NAME " v" PROJECT_VERSION "\n");

    if (glfwInit() == GLFW_FALSE) {
        fprintf(stderr, "GLFW initialization failed!");
        return 1;
    }

    glfwSetErrorCallback(errorCallback);

    printf("Starting...\n");
    //NOTE: Let's require a certain (old) version of OpenGL or newer...
    //Like OpenGL 2.0+:
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(800, 600, "TEST WINDOW", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create window or OpenGL context!");
        //TODO: try-finally-like handling from C#.. I wonder how to do that here:
        glfwTerminate();
        return 2;
    }

    this_thread::sleep_for(chrono::milliseconds(3000));
    printf("Done testing!\n");

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
