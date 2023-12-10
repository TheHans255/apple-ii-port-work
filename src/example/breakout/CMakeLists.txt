add_executable(apple-iie-example-breakout main.c rand.c sound.c)
target_compile_options(apple-iie-example-breakout PRIVATE -Os -flto)
set_target_properties(apple-iie-example-breakout PROPERTIES OUTPUT_NAME "breakout.sys")

target_link_libraries(apple-iie-example-breakout apple-iie-prodos-cli -static)
