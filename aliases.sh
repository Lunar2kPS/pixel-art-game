#!/bin/bash

ignoreScripts=(
    "get-platform-default-config"
    "get-platform"
)

printf "Adding aliases for the bash scripts under ./scripts...\n"
for filePath in "./scripts/"*; do
    fileName=$(basename $filePath)
    aliasName=${fileName/.sh/}

    ignore=false
    for ignoreName in "${ignoreScripts[@]}"; do
        if [ "$aliasName" == "$ignoreName" ]; then
            ignore=true
            break
        fi
    done

    if [ $ignore == true ]; then
        continue
    fi

    printf "%-5s%-30s\n" " - " "$aliasName"
    alias $aliasName="$filePath"
done
