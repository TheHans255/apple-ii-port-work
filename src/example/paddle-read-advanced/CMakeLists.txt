add_executable(apple-ii-example-paddle-read main.c)
target_compile_options(apple-ii-example-paddle-read PRIVATE -Os -flto)
set_target_properties(apple-ii-example-paddle-read PROPERTIES OUTPUT_NAME "paddle_read.sys")

target_link_libraries(apple-ii-example-paddle-read apple-ii apple-ii-prodos apple-ii-prodos-stdlib -static)