add_library(apple-iie INTERFACE)

target_link_libraries(apple-iie INTERFACE apple-ii -static)
target_compile_options(apple-iie INTERFACE -Os -flto)
target_include_directories (apple-iie INTERFACE .)
