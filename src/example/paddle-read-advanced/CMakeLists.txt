add_executable(apple-iie-example-paddle-read main.c)
target_compile_options(apple-iie-example-paddle-read PRIVATE -Os -flto)
set_target_properties(apple-iie-example-paddle-read PROPERTIES OUTPUT_NAME "paddle_read.sys")

target_link_libraries(apple-iie-example-paddle-read apple-iie-prodos-cli -static)
