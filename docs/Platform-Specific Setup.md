# Platform-Specific Setup

## Windows
### Installing Development Dependencies
#### [CMake](https://cmake.org)
Download and run the installer for [CMake](https://cmake.org/download), and make sure to add CMake to your path for all users.

#### [LLVM (for Clang and Clang++)](https://releases.llvm.org/download.html)
Download the latest version of [LLVM from their GitHub releases](https://github.com/llvm/llvm-project/releases).
For example, look for the file whose name is like the following: **LLVM-15.0.6-win64.exe**.
Run the installer, and make sure to add LLVM to your path for all users.

#### [Ninja (Build System)](https://ninja-build.org/)
Download the latest binary from [Ninja's GitHub releases](https://github.com/ninja-build/ninja/releases).
Extract the ZIP, which contains the Ninja's executable main program.
Put the ninja.exe file under `C:/Program Files/ninja-win/ninja.exe` (for example), and add that folder to your PATH variable.

:information_source: NOTE: You'll need to restart your computer _(or restart VS Code from a fresh terminal with the updated PATH variable)_ for this to take effect in VS Code.


---


## MacOS
### Installing Development Dependencies
#### [CMake](https://cmake.org)
After downloading the .dmg file from https://cmake.org/download and moving the CMake application under `/Applications`, you'll want to add it to your path with something like the following:

```sh
sudo ln -s /Applications/CMake.app/Contents/bin/cmake /usr/local/bin/cmake
make --version
```

You should see the CMake version correctly print out, indicating it's been downloaded onto your system with a symlink placed under an existing PATH-contained folder.


---


## Linux
### Installing Development Dependencies
#### Clang Compiler
`sudo apt install clang`

#### [CMake](https://cmake.org)
:warning: Trying to install CMake from `sudo apt install cmake` may install an outdated version! (Such as 3.16.3).

Instead, download the executable .sh script from [CMake's website](https://cmake.org/download),
Navigate to your downloads folder in a terminal, and run a command similar to the following:

```sh
chmod +rwx cmake-3.25.1-linux-x86_64.sh --skip-license --prefix=/opt/cmake
sudo ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
cmake --version
```

You should see the CMake version correctly print out, indicating it's been downloaded onto your system with a symlink placed under an existing PATH-contained folder.

#### Building GLFW _(from source files, brought in as a Git submodule)_
To build GLFW along with this project, follow their [compile guide](https://www.glfw.org/docs/latest/compile_guide.html). To find out if your Linux machine is using the X11 or Wayland windowing system, go to Settings -> About. You should find a field that says "Windowing System", with a value such as X11.
