#pragma once

#if defined _WIN32
    #define WINDOWS
#elif defined __APPLE__
    #define MACOS
#elif defined __linux__
    #define LINUX
#else
    #define UNKNOWN_PLATFORM
#endif

inline const char* getPlatformName() {
    return 
#if defined WINDOWS
        "Windows"
#elif defined MACOS
        "MacOS"
#elif defined LINUX
        "Linux"
#else
        "UNKNOWN"
#endif
    ;
}
