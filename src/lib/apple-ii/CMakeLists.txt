add_library(apple-ii
    apple-ii-monitor.c
)

target_compile_options(apple-ii PRIVATE -Os -flto)
target_include_directories (apple-ii PUBLIC .)