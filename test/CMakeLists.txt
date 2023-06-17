# Copyright (c) 2023 Robarm
# All rights reserved

set(project_name robarm_test)

set(test_target pwm)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)

set(sources
    ${sources_dir}/${test_target}_test.cpp
)

set(robarm_executable robarm_test)

link_libraries("-static")

add_executable(${robarm_executable} ${sources})

target_link_libraries(${robarm_executable} LINK_PUBLIC
    robarm_module_led
    robarm_module_button
    robarm_module_motor
    robarm_module_accelerometer
)
