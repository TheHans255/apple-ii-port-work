add_executable(apple-ii-port-test main.c)
target_compile_options(apple-ii-port-test PRIVATE -Os -flto)
set_target_properties(apple-ii-port-test PROPERTIES OUTPUT_NAME "hello.sys")

target_link_libraries(apple-ii-port-test apple-ii apple-ii-prodos apple-ii-prodos-stdlib -static)