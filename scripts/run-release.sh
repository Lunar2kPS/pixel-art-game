#!/bin/bash

source $(dirname $0)"/get-platform-default-config.sh"

./out/build/$defaultConfig/PixelArtGame.exe
