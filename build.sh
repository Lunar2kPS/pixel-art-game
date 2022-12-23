#!/bin/bash

# This is a helper script to build when Visual Studio is not available
#       (For example, when developing on MacOS or Linux systems).
# The default configuration is x64-release, but you may pass a different config as an argument.
# To see the available values, see the "name" values of the configurationPresets array in CMakePresets.json

# COMMAND LINE USAGE:
# ./build.sh [CONFIG]

# EXAMPLES:
#       ./build.sh x64-release
#       ./build.sh x64-debug

defaultConfig="x64-release"

argCount=$#
args=("$@")

if [ $argCount -gt 0 ]; then
    config=${args[0]}
else
    config="$defaultConfig"
fi

printf "Building $config...\n\n"
printf "Running CMake...\n"
# cmake  ..
cmake --preset "$config"

exitCode=$?
if [ $exitCode -ne 0 ]; then
    exit $exitCode
fi
printf "\n"

printf "Running CMake build system...\n"
# cmake --build .
cmake --build out/build/"$config"
exitCode=$?
if [ $exitCode -ne 0 ]; then
    exit $exitCode
fi

printf "\nSUCCESS!"