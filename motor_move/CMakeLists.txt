add_executable(motor_move
motor_move.c
        )

# pull in common dependencies
target_link_libraries(motor_move pico_stdlib hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(motor_move)
