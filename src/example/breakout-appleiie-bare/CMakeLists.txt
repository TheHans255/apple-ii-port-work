add_executable(apple-iie-bare-example-breakout 
    main.c
    paddle.c
    rand.c 
    sound.c
    text-lores-io.c)
target_compile_options(apple-iie-bare-example-breakout PRIVATE -Os -flto)
set_target_properties(apple-iie-bare-example-breakout PROPERTIES OUTPUT_NAME "breakout.bin")

target_link_libraries(apple-iie-bare-example-breakout apple-iie-bare -static)
