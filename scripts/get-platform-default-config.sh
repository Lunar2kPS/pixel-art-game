#!/bin/bash

source $(dirname $0)"/get-platform.sh"
case "$simpleOSName" in
    "Windows") defaultConfig="windows-x64-release";;
    "MacOS") defaultConfig="macos-x64-release";;
    "Linux") defaultConfig="linux-x64-release";;
    "Unknown")
        printf "Unrecognized platform! Unable to build.\n"
        exit 0 ;;
esac
