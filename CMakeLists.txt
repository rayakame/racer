cmake_minimum_required(VERSION 3.20)
project(racer C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UBSan" OFF)


function(racer_configure_target target)
    target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wshadow -Wconversion
            "-fmacro-prefix-map=${CMAKE_SOURCE_DIR}/="
    )
    if(ENABLE_SANITIZERS)
        target_compile_options(${target} PRIVATE
                -fsanitize=address,undefined
                -fno-omit-frame-pointer
        )
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
endfunction()

# Externe Libs
set(MINIFB_BUILD_EXAMPLES     OFF CACHE BOOL "" FORCE)
set(MINIFB_BUILD_TESTS        OFF CACHE BOOL "" FORCE)
set(MINIFB_BUILD_VERSION_INFO OFF CACHE BOOL "" FORCE)
set(MINIFB_USE_OPENGL_API     OFF CACHE BOOL "" FORCE)
add_subdirectory(external/minifb)

# core: simulation, physic, AI.
add_library(core STATIC
        src/core/linalg.c
        src/core/log.c
)
target_include_directories(core PUBLIC src)
if(UNIX)
    target_link_libraries(core PUBLIC m)
endif()
racer_configure_target(core)

# Game with window
add_executable(racer
        src/game/main.c
        src/platform/platform_minifb.c
)
target_link_libraries(racer PRIVATE core minifb)
racer_configure_target(racer)

# headless training
add_executable(trainer
        src/trainer/main.c
)
target_link_libraries(trainer PRIVATE core)
racer_configure_target(trainer)