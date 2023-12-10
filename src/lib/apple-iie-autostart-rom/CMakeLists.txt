add_library(apple-iie-autostart-rom INTERFACE)

target_link_libraries(apple-iie-autostart-rom INTERFACE
    apple-iie 
    apple-ii-autostart-rom
    -static)
    
target_include_directories (apple-iie-autostart-rom INTERFACE .)