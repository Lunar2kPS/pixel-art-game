#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GameVersion.h"
#include "platforms.h"

#include "IndexBuffer.h"
#include "OpenGLUtil.h"
#include "Texture.h"
#include "Renderer.h"
#include "Resources.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

using namespace glm;
using std::stringstream;

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

        const int VERTEX_COUNT = 6;
        const int VERTEX_COORD_COUNT = 3 * VERTEX_COUNT + 2 * VERTEX_COUNT; //pos.xyz and uv.xy
        const int INDEX_COUNT = 12;
        float r = 0.5f;

        vec2 sheetTiles = vec2(8, 8);
        vec2 sheetTileUVDistance = vec2(1 / sheetTiles.x, 1 / sheetTiles.y);

        vec2 tile = vec2(1, 0);

        //Triangle layout:
        //           5
        //          /|
        //  1-----3\ |
        //  | \   | \4
        //  |   \ | /
        //  0-----2
        

        //My attempted space:
        //Left-handed coords XYZ:
        //     +y
        //      ^
        //      |  +z
        //      | /
        //      |/
        //      ------> +x

        float verts[VERTEX_COORD_COUNT] = {
            -r, -r, -r, tile.x * sheetTileUVDistance.x, 1 - ((tile.y + 1) * sheetTileUVDistance.y),
            -r,  r, -r, tile.x * sheetTileUVDistance.x, 1 - (tile.y * sheetTileUVDistance.y),
            r, -r, -r, (tile.x + 1) * sheetTileUVDistance.x, 1 - ((tile.y + 1) * sheetTileUVDistance.y),
            r,  r, -r, (tile.x + 1) * sheetTileUVDistance.x, 1 - (tile.y * sheetTileUVDistance.y),

            r, -r, r, (tile.x + 2) * sheetTileUVDistance.x, 1 - ((tile.y + 1) * sheetTileUVDistance.y),
            r, r, r, (tile.x + 2) * sheetTileUVDistance.x, 1 - (tile.y * sheetTileUVDistance.y)
        };

        unsigned int indices[INDEX_COUNT] = {
            0, 1, 2,
            3, 2, 1,

            2, 3, 4,
            5, 4, 3
        };

        VertexArray vao;
        VertexBuffer vb = VertexBuffer(verts, VERTEX_COORD_COUNT * sizeof(float));
        IndexBuffer ib = IndexBuffer(indices, INDEX_COUNT);
        
        VertexBufferLayout layout;

        //FIXME: Linux error, see VertexBufferLayout.h for more details.
        // layout.push<float>(3);
        layout.pushFloat(3);        //pos.xyz
        layout.pushFloat(2);        //uv.xy

        vao.addBuffer(vb, layout);

        Shader shader = Shader("resources/shaders/Basic.glsl");
        Texture tex = Texture("resources/spritesheets/Terrain Tiles.png");

        shader.bind();
        tex.bind(); //NOTE: Slot 0
        shader.setUniform1i("uniformTexture", 0); //NOTE: Corresponds to slot 0
        shader.setUniform4f("uniformColor", 1, 1, 1, 1);

        //NOTE: VSYNC ON! Huge performance benefits..
        glfwSwapInterval(1);

        //CLEAR STATE
        shader.unbind();
        vao.unbind();
        vb.unbind();
        ib.unbind();

        Renderer renderer;

        //NOTE: Alpha blending enabled:
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        GLCall(glEnable(GL_CULL_FACE));
        GLCall(glCullFace(GL_BACK));
        GLCall(glFrontFace(GL_CW));

        int windowWidth;
        int windowHeight;

        enum class MovementMode {
            Sprite = 0,
            Camera = 1
        };
        MovementMode moveTarget = MovementMode::Sprite;
        float timeLastSwitched = 0;
        vec3 modelPosition = vec3(0, 0, 2);
        vec3 cameraPosition = vec3(0);

        float prevTime = glfwGetTime();
        while (!glfwWindowShouldClose(window)) {
            glfwGetWindowSize(window, &windowWidth, &windowHeight);

            float time = glfwGetTime();
            float dt = time - prevTime;

            shader.bind();


            vec3 input = vec3(0);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                input.x--;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                input.x++;
                
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                input.y--;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                input.y++;

            if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
                input.z--;
            if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
                input.z++;

            if (glfwGetKey(window, GLFW_KEY_0) && time - timeLastSwitched > 1) {
                moveTarget = (MovementMode) ((int) moveTarget + 1);
                if ((int) moveTarget > 1)
                    moveTarget = (MovementMode) 0;
                timeLastSwitched = time;
                printf("moveTarget = %d\n", moveTarget);
            }

            vec3 deltaPosition = r * 10 * dt * input;
            switch (moveTarget) {
                case MovementMode::Sprite:
                    modelPosition += deltaPosition;
                    break;
                case MovementMode::Camera:
                    cameraPosition += deltaPosition;
                    break;
            }

            //NOTE: mat4(1) seems to be the identity matrix. I don't really understand their docs too well..
            mat4 modelMatrix = mat4(1);            
            modelMatrix = glm::translate(modelMatrix, modelPosition);
            modelMatrix = glm::rotate(modelMatrix, (float) 2 * time, vec3(0, 1, 0));
            
            mat4 viewMatrix = mat4(1);
            viewMatrix = glm::translate(viewMatrix, -cameraPosition);

            mat4 projectionMatrix = //mat4(1);
            // glm::ortho(
            //     (float) -windowWidth / 2,
            //     (float) windowWidth / 2,
            //     (float) -windowHeight / 2,
            //     (float) windowHeight / 2,
            //     (float) 0.01f,
            //     (float) 1000
            // );

            glm::perspective(
                (float) glm::radians((float) 60),
                (float) windowWidth / (float) windowHeight,
                (float) 0.01f,
                (float) 1000
            );

            //NOTE: Because NDC in OpenGL is [-1, 1] in XY axes,
            //I set the ortho camera ranges to -1/2 to +1/2 of width and height to match.
            //That way, a camera at the world origin, back some -Z units, will see objects at (0, 0, 0) in the center of the screen.

            //NOTE: PVM ordering because of column-major matrices. It's weird.
            mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
            shader.setUniformMatrix4fv("uniformMVP", mvp);
            
            ib.bind();

            renderer.clear();
            renderer.draw(vao, ib, shader);

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
