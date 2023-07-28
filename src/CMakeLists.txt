cmake_minimum_required (VERSION 3.27.0)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project (apple-ii-port-test C ASM)

# TODO: This should be set inside the prodos library instead
# (this will be done automatically during the SDK extension)
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/apple-ii-prodos/link.ld)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

add_subdirectory(apple-ii)
add_subdirectory(apple-ii-prodos)

add_executable(apple-ii-port-test main.c)
target_compile_options(apple-ii-port-test PRIVATE -Os -flto)
set_target_properties(apple-ii-port-test PROPERTIES OUTPUT_NAME "hello.sys")

target_link_libraries(apple-ii-port-test apple-ii apple-ii-prodos -static)