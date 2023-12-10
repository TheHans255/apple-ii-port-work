add_library (apple-iie-prodos STATIC
    prodos-syscall-core.S
    prodos-syscall.c
)

target_compile_options(apple-iie-prodos PUBLIC -Os -flto)

target_link_libraries(apple-iie-prodos PUBLIC
    apple-ii
    apple-iie
    apple-ii-autostart-rom
    apple-iie-autostart-rom
)

target_include_directories (apple-iie-prodos PUBLIC .)
