# forward the SDL2 include directory so SDL_Image includes work
include_directories("${RAFT_INCLUDE_DIR}/SDL2")

# Setup the correct spot where SDL is built to for the SDL libs
add_library(SDL2 SHARED IMPORTED GLOBAL)
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION "${RAFT_INSTALL_DIR}/bin/SDL2d.dll")
    if (MSVC)
        set_property(TARGET SDL2 PROPERTY IMPORTED_IMPLIB "${RAFT_LIB_DIR}/SDL2d.lib")
    else()
        set_property(TARGET SDL2 PROPERTY IMPORTED_IMPLIB "${RAFT_LIB_DIR}/libSDL2d.dll.a")
    endif()
else()
    set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION "${RAFT_INSTALL_DIR}/bin/SDL2.dll")
    if (MSVC)
        set_property(TARGET SDL2 PROPERTY IMPORTED_IMPLIB "${RAFT_LIB_DIR}/SDL2.lib")
    else()
        set_property(TARGET SDL2 PROPERTY IMPORTED_IMPLIB "${RAFT_LIB_DIR}/libSDL2.dll.a")
    endif()
endif()

# SDL_Image uses the SDL2::SDL2 alias, so set this up as well
add_library(SDL2::SDL2 ALIAS SDL2)

# Set a different target for the SDL libs so they don't go looking for SDL themselves as we have already told them where to find SDL above
set (TARGET "Ancona")
