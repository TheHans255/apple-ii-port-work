add_library(apple-iie-prodos-cli INTERFACE)

target_link_libraries(apple-iie-prodos-cli INTERFACE apple-iie-prodos-stdlib -static)

target_include_directories (apple-iie-prodos-cli INTERFACE .)