add_executable(encoder
encoder.c
        )

# pull in common dependencies
target_link_libraries(encoder pico_stdlib hardware_timer hardware_gpio)

pico_enable_stdio_usb(encoder 1)
pico_enable_stdio_uart(encoder 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(encoder)
