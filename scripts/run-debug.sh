#!/bin/bash

source $(dirname $0)"/get-platform-default-config.sh"
defaultDebugConfig=${defaultConfig/release/debug}

case "$simpleOSName" in
    "Windows")      ./out/build/$defaultDebugConfig/PixelArtGame.exe;;
    "MacOS")        ./out/build/$defaultDebugConfig/PixelArtGame;;
    "Linux")        ./out/build/$defaultDebugConfig/PixelArtGame;;
esac
