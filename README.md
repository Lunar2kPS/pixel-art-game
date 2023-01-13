# Pixel Art Game
This is a fun passion/learning project, based on [TheCherno's](https://www.youtube.com/c/TheChernoProject) [Game Programming Series](https://www.youtube.com/watch?v=GFYT7Lqt1h8&list=PLlrATfBNZ98eOOCk2fOFg7Qg5yoQfFAdf&index=1).

## Overview of the Project
![Preview of the project's work-in-progress](./docs/images/Current%20Game%20Progress.png)

This project is in C++ using the following, despite the original tutorial series being in Java:
- CMake
- clang/clang++,
- Ninja (on Windows)
- Unix Makefiles (on Linux)
- Bash

**Current status:**
- :white_check_mark: I've setup the project with GLFW/OpenGL (using an OpenGL extension library GLAD to retrieve the latest OpenGL 4.1+ functions), and have begun basic rendering commands in C++/OpenGL/GLSL!
- :hammer_and_wrench: I'm currently working on fixing the rendering of the grass tiles now, and then will add a basic player with movement around the game world.


## Getting Started (for Developers)
### Git Submodules (Note)
In order to build this project, you'll need to clone this repo's Git submodules with:
```sh
git submodule update --init --recursive
```

### Building & Running the Project
Once your [development environment is setup](./docs/Platform-Specific%20Setup.md), you can run the following on any platform _(Windows, MacOS, or Linux)_:

```sh
# This creates an alias for each of the scripts under the ./scripts folder!
# Run it and see the output of each of the aliases it creates.
source ./aliases.sh

# This calls the build.sh and run-release.sh scripts under the scripts folder, using aliases:
build && run-release
```

## References
- [How to setup OpenGL with pixel-perfect rendering](https://gamedev.stackexchange.com/questions/103334/how-can-i-set-up-a-pixel-perfect-camera-using-opengl-and-orthographic-projection)
- [LearnOpenGL.com -- Hello Window](https://learnopengl.com/Getting-started/Hello-Window)
- [My previous OpenGL tutorial progress](https://github.com/2kCarlos/intro-to-cpp-opengl)
  - _This will likely be important in abstracting some OpenGL features, but this project will take a 2D-first approach for drawing sprites rather than focusing on 3D geometry and 3D scenes._
- [OpenGL Docs](https://docs.gl)
