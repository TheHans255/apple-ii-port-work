add_library (apple-ii-prodos
    prodos-syscall-core.S
    prodos-syscall.c
)

target_compile_options(apple-ii-prodos PRIVATE -Os -flto)

target_link_libraries(apple-ii-prodos apple-ii)

target_include_directories (apple-ii-prodos PUBLIC .)