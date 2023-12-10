add_library(apple-ii-bare INTERFACE)
target_link_libraries(apple-ii-bare INTERFACE 
    apple-ii 
    crt0 
    init-stack 
    exit-return
    -static)
target_compile_options(apple-ii-bare INTERFACE -Os -flto)
target_include_directories (apple-ii-bare INTERFACE .)
