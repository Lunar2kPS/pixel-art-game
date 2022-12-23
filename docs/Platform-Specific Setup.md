# Platform-Specific Setup
## Linux
### Installing Development Dependencies
#### Clang Compiler
`sudo apt install clang`

#### CMake
:warning: Trying to install CMake from `sudo apt install cmake` may install an outdated version! (Such as 3.16.3).

Instead, download the executable .sh script from [CMake's website](https://cmake.org),
Navigate to your downloads folder in a terminal, and run a command similar to the following:

```sh
chmod +rwx cmake-3.25.1-linux-x86_64.sh --skip-license --prefix=/opt/cmake
sudo ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
cmake --version
```

You should see the CMake version correctly print out, indicating it's been downloaded onto your system with a symlink placed under an existing PATH-contained folder.

#### Building GLFW _(from source files, brought in as a Git submodule)_
To build GLFW along with this project, follow their [compile guide](https://www.glfw.org/docs/latest/compile_guide.html). To find out if your Linux machine is using the X11 or Wayland windowing system, go to Settings -> About. You should find a field that says "Windowing System", with a value such as X11.


### Building on Linux (X11)
You may want to make all of the top-level scripts executable:

`chmod +rwx ./*.sh`

:warning: :hammer_and_wrench: We need to update the bash scripts and CMakePresets.json to be cross-platform, so in the meantime, use the following commands to build the C++ project:

```sh
cmake . -B out
cmake --build out
```

Then to run it:
```sh
./out/PixelArtGame
```
