#if __EMSCRIPTEN__

#define BROWSER_PLATFORM
#define OPENGLES3_API

#define SDL2_IMP

#elif __linux__

#define LINUX_PLATFORM
#define OPENGLES3_API
#define SDL2_IMP

#elif __APPLE__

#define MACOS_PLATFORM
#define OPENGLES3_API
#define SDL2_IMP 

#elif _WIN32

#define WINDOWS_PLATFORM
#define OPENGLES3_API
#define SDL2_IMP

#elif __unix__

#define UNIX_PLATFORM
#define OPENGLES3_API
#define SDL2_IMP

#endif