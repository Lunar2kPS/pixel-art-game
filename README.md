# Pixel Art Game
This is a fun passion/learning project, based on [TheCherno's](https://www.youtube.com/c/TheChernoProject) [Game Programming Series](https://www.youtube.com/watch?v=GFYT7Lqt1h8&list=PLlrATfBNZ98eOOCk2fOFg7Qg5yoQfFAdf&index=1).

This project is in C++ using the following, despite the original tutorial series being in Java:
- CMake
- clang/clang++,
- Ninja (on Windows)
- Unix Makefiles (on Linux)
- Bash

This is a great way for me to learn C++ while having a goal in mind (creating a simple pixel art game)!

First, I need to learn how to setup the project with GLFW/OpenGL, then start to draw pixels to the screen.

## Getting Started (for Developers)
### Git Submodules (Note)
In order to build this project, you'll need to clone this repo's Git submodules with:
```sh
git submodule update --init --recursive
```

**See also:**
### [Platform-Specific Setup](./docs/Platform-Specific%20Setup.md)

## References
- [How to setup OpenGL with pixel-perfect rendering](https://gamedev.stackexchange.com/questions/103334/how-can-i-set-up-a-pixel-perfect-camera-using-opengl-and-orthographic-projection)
- [LearnOpenGL.com -- Hello Window](https://learnopengl.com/Getting-started/Hello-Window)
- [My previous OpenGL tutorial progress](https://github.com/2kCarlos/intro-to-cpp-opengl)
  - _This will likely be important in abstracting some OpenGL features, but this project will take a 2D-first approach for drawing sprites rather than focusing on 3D geometry and 3D scenes._
- [OpenGL Docs](https://docs.gl)
