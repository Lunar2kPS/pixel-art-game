#!/bin/bash

source $(dirname $0)"/get-platform-default-config.sh"
defaultDebugConfig=${defaultConfig/release/debug}

./out/build/$defaultDebugConfig/PixelArtGame.exe
