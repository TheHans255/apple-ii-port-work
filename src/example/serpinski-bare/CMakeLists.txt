add_executable(apple-ii-bare-example-serpinski 
    main.c
    hires.c
    rand.c)
target_compile_options(apple-ii-bare-example-serpinski PRIVATE -Os -flto)
set_target_properties(apple-ii-bare-example-serpinski PROPERTIES OUTPUT_NAME "serpinski.bin")

target_link_libraries(apple-ii-bare-example-serpinski apple-ii-bare -static)
