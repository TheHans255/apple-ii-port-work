add_executable(apple-iie-example-prodos-showcase
    prodos-showcase.c
    io-buffer-alloc.c
    )
target_compile_options(apple-iie-example-prodos-showcase PRIVATE -Os -flto)
set_target_properties(apple-iie-example-prodos-showcase PROPERTIES OUTPUT_NAME "pd.showcase.sys")

target_link_libraries(apple-iie-example-prodos-showcase apple-iie-prodos-cli -static)
