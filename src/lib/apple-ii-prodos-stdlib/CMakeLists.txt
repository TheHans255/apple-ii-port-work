add_library (apple-ii-prodos-stdlib
    char-io.c
    prodos-exit.c
)

target_compile_options(apple-ii-prodos-stdlib PRIVATE -Os -flto)

target_link_libraries(apple-ii-prodos-stdlib apple-ii apple-ii-prodos crt0 init-stack exit-custom)

target_include_directories (apple-ii-prodos-stdlib PUBLIC .)