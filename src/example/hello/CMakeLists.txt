add_executable(apple-iie-example-hello main.c)
target_compile_options(apple-iie-example-hello PRIVATE -Os -flto)
set_target_properties(apple-iie-example-hello PROPERTIES OUTPUT_NAME "hello.sys")

target_link_libraries(apple-iie-example-hello apple-iie-prodos-cli -static)
