add_library (apple-iie-prodos-stdlib STATIC
    prodos-char-io.c
    prodos-exit.c
)

target_compile_options(apple-iie-prodos-stdlib PUBLIC -Os -flto)

target_link_libraries(apple-iie-prodos-stdlib PUBLIC
    apple-iie-prodos
    crt0 
    init-stack 
    exit-custom -static)

target_include_directories (apple-iie-prodos-stdlib PUBLIC .)
