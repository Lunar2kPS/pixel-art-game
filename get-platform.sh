#/bin/bash

# These are regexes to compare against $(uname) and $OSTYPE.

# WARNING: The case-insensitive modifier (?i)...(?-i) did NOT work for me
# on MINGW (Windows), so I'm avoiding it in the regex patterns! (using lowercase instead)
windowsNamePattern="(mingw)|(msys)"
macOSNamePattern="darwin"
linuxNamePattern="linux"

lowercaseUName=$(uname | tr '[:upper:]' '[:lower:]')
lowercaseOSType=$(echo "$OSTYPE" | tr '[:upper:]' '[:lower:]')

# Examples values per-platform:
#   Windows:
#       uname       MINGW64_NT-10.0-19044
#       $OSTYPE     msys
#   MacOS:
#       uname       Darwin
#       $OSTYPE     darwin21
#   Linux:
#       uname       Linux
#       $OSTYPE     linux-gnu

simpleOSName="Unknown"
if [[ $lowercaseUName =~ $windowsNamePattern ]]; then
    printf "WIN A\n"
fi
if [[ $lowercaseOSType =~ $windowsNamePattern ]]; then
    printf "WIN B\n"
fi
if [[ $lowercaseUName =~ $macOSNamePattern ]]; then
    printf "MAC A\n"
fi
if [[ $lowercaseOSType =~ $macOSNamePattern ]]; then
    printf "MAC B\n"
fi
if [[ $lowercaseUName =~ $linuxNamePattern ]]; then
    printf "LINUX A\n"
fi
if [[ $lowercaseOSType =~ $linuxNamePattern ]]; then
    printf "LINUX B\n"
fi
