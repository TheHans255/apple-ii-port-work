add_library(apple-iie-prodos-hires INTERFACE)

target_link_libraries(apple-iie-prodos-hires INTERFACE apple-iie-prodos-stdlib -static)

target_include_directories (apple-iie-prodos-hires INTERFACE .)