#!/bin/bash

source $(dirname $0)"/get-platform-default-config.sh"

case "$simpleOSName" in
    "Windows")      ./out/build/$defaultConfig/PixelArtGame.exe;;
    "MacOS")        ./out/build/$defaultConfig/PixelArtGame;;
    "Linux")        ./out/build/$defaultConfig/PixelArtGame;;
esac
