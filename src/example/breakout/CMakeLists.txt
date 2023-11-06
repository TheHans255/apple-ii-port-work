add_executable(apple-ii-example-breakout main.c rand.c sound.c)
target_compile_options(apple-ii-example-breakout PRIVATE -Os -flto)
set_target_properties(apple-ii-example-breakout PROPERTIES OUTPUT_NAME "breakout.sys")

target_link_libraries(apple-ii-example-breakout apple-ii apple-ii-prodos apple-ii-prodos-stdlib -static)
