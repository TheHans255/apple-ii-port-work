add_library(apple-iie-bare INTERFACE)
target_link_libraries(apple-iie-bare INTERFACE 
    apple-iie
    crt0 
    init-stack 
    exit-loop
    -static)
target_compile_options(apple-iie-bare INTERFACE -Os -flto)
target_include_directories (apple-iie-bare INTERFACE .)
