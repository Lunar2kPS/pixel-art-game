#!/bin/bash

source $(dirname $0)"/get-platform-default-config.sh"
source $(dirname $0)"/get-project-name.sh"
defaultDebugConfig=${defaultConfig/release/debug}

case "$simpleOSName" in
    "Windows")      ./out/build/$defaultDebugConfig/$projectName.exe;;
    "MacOS")        ./out/build/$defaultDebugConfig/$projectName;;
    "Linux")        ./out/build/$defaultDebugConfig/$projectName;;
esac
