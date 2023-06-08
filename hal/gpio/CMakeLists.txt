# Copyright (c) 2023 Robarm
# All rights reserved

set(project_name robarm_hal_gpio)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)
set(headers_dir ${CMAKE_CURRENT_LIST_DIR}/include)

set(sources
    ${sources_dir}/gpio_component.cpp
    ${sources_dir}/digital_input.cpp
    ${sources_dir}/digital_output.cpp
)
set(headers
    ${headers_dir}/gpio_component.hpp
    ${headers_dir}/digital_input.hpp
    ${headers_dir}/digital_output.hpp
)

add_library(${project_name} STATIC ${sources} ${headers})

set_target_properties(${project_name} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

target_include_directories(${project_name} PUBLIC ${robarm_dir})

target_link_libraries(${project_name} LINK_PUBLIC
    robarm_hal_device
)
