add_executable(class_motor
class_motor.cpp
        )

# pull in common dependencies
target_link_libraries(class_motor pico_stdlib 
                                hardware_pwm 
                                hardware_timer 
                                hardware_gpio)

pico_enable_stdio_usb(class_motor 1)
pico_enable_stdio_uart(class_motor 0)
# create map/bin/hex file etc.
pico_add_extra_outputs(class_motor)
