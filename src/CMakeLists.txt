cmake_minimum_required (VERSION 3.27.0)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project (apple-ii-port-work C ASM)

# TODO: This should be set inside the prodos library instead
# (this will be done automatically during the SDK extension)
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/lib/apple-ii-bare/link.ld)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

add_subdirectory(lib/apple-ii)
add_subdirectory(lib/apple-iie)
add_subdirectory(lib/apple-ii-bare)
add_subdirectory(lib/apple-iie-bare)

add_subdirectory(example/breakout-appleiie-bare)
add_subdirectory(example/serpinski-bare)
