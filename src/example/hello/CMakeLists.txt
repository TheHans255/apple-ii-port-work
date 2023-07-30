add_executable(apple-ii-example-hello main.c)
target_compile_options(apple-ii-example-hello PRIVATE -Os -flto)
set_target_properties(apple-ii-example-hello PROPERTIES OUTPUT_NAME "hello.sys")

target_link_libraries(apple-ii-example-hello apple-ii apple-ii-prodos apple-ii-prodos-stdlib -static)