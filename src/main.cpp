#include <stdio.h>
#include <thread>

#include <GLFW/glfw3.h>
#include "GameVersion.h"

using namespace std;

int main() {
    printf(PROJECT_NAME " v" PROJECT_VERSION "\n");

    if (glfwInit() == GLFW_FALSE) {
        printf("GLFW initialization failed!");
        return 1;
    }

    printf("Starting...\n");
    this_thread::sleep_for(chrono::milliseconds(3000));
    printf("Done testing!\n");

    glfwTerminate();
    return 0;
}
