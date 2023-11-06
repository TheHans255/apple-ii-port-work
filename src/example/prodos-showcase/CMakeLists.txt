add_executable(apple-ii-example-prodos-showcase
    prodos-showcase.c
    prodos-combo-buffer.c
)
target_compile_options(apple-ii-example-prodos-showcase PRIVATE -Os -flto)
set_target_properties(apple-ii-example-prodos-showcase PROPERTIES OUTPUT_NAME "pd.showcase.sys")

target_link_libraries(apple-ii-example-prodos-showcase apple-ii apple-ii-prodos apple-ii-prodos-stdlib -static)
