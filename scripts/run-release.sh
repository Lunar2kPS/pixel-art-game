#!/bin/bash

source $(dirname $0)"/get-platform-default-config.sh"
source $(dirname $0)"/get-project-name.sh"

case "$simpleOSName" in
    "Windows")      ./out/build/$defaultConfig/$projectName.exe;;
    "MacOS")        ./out/build/$defaultConfig/$projectName;;
    "Linux")        ./out/build/$defaultConfig/$projectName;;
esac
