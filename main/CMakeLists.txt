# Copyright (c) 2023 Robarm
# All rights reserved

set(project_name robarm_main)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)

set(sources
    ${sources_dir}/main.cpp
)

set(robarm_executable robarm)

link_libraries("-static")

add_executable(${robarm_executable} ${sources})

target_link_libraries(${robarm_executable} LINK_PUBLIC
    robarm_hal_pwm
    robarm_module_led
    robarm_module_accelerometer
    robarm_module_button
    robarm_module_roboticarm
)
