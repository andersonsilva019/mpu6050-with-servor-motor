# Copyright (c) 2023 Robarm
# All rights reserved

set(project_name robarm_hal_pwm)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)
set(headers_dir ${CMAKE_CURRENT_LIST_DIR}/include)

set(sources
    ${sources_dir}/pwm_component.cpp
    ${sources_dir}/pwm_info.cpp
)
set(headers
    ${headers_dir}/pwm_component.hpp
    ${headers_dir}/pwm_info.hpp
)

add_library(${project_name} STATIC ${sources} ${headers})

set_target_properties(${project_name} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

target_include_directories(${project_name} PUBLIC ${robarm_dir})

target_link_libraries(${project_name} LINK_PUBLIC
    robarm_hal_device
    robarm_utils_common
)
