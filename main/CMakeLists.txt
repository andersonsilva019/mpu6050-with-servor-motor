# Copyright (c) 2023 Robarm
# All rights reserved

set(project_name robarm_main)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)

set(sources
    ${sources_dir}/main.cpp
)

set(robarm_executable robarm)

add_executable(${robarm_executable} ${sources})

target_link_libraries(${robarm_executable} LINK_PUBLIC
    robarm_module_led
)
