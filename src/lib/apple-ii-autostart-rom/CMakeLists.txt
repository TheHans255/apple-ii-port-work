add_library(apple-ii-autostart-rom STATIC
    apple-ii-monitor.c
)
target_link_libraries(apple-ii-autostart-rom PUBLIC apple-ii -static)
target_compile_options(apple-ii-autostart-rom PUBLIC -Os -flto)
target_include_directories (apple-ii-autostart-rom PUBLIC .)
