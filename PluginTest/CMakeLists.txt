cmake_minimum_required(VERSION 3.16)
project(plugin_demo CXX)
set(CMAKE_CXX_STANDARD 20)

# ── host binary ──────────────────────────────────────────────────────────────
add_executable(plugin_host main.cpp)
# dl è la libreria del dynamic linker (dlopen, dlsym, dlclose).
# Su Linux è una lib separata; su macOS è inclusa nel sistema.
target_link_libraries(plugin_host PRIVATE dl)

# ── plugin shared libraries ───────────────────────────────────────────────────
# SHARED → produce un .so (Linux) / .dylib (macOS)

add_library(plugin_upper  SHARED plugin_upper.cpp)
add_library(plugin_reverse SHARED plugin_reverse.cpp)

# I plugin devono vedere plugin_api.h
target_include_directories(plugin_upper   PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(plugin_reverse PRIVATE ${CMAKE_SOURCE_DIR})

# Su Linux: -fPIC è necessario per le shared library.
# CMake lo imposta automaticamente con SHARED, ma lo esplicitiamo per chiarezza.
# Il prefisso "lib" viene rimosso per chiarezza (non è obbligatorio).
set_target_properties(plugin_upper plugin_reverse PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    PREFIX ""   # evita il prefisso "lib" → plugin_upper.so invece di libplugin_upper.so
)
