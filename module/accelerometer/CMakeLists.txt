# Copyright (c) 2023 Robarm
# All rights reserved

set(project_name robarm_module_accelerometer)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)
set(headers_dir ${CMAKE_CURRENT_LIST_DIR}/include)

set(sources
    ${sources_dir}/accelerometer.cpp
    ${sources_dir}/accelerometer_exception.cpp
    ${sources_dir}/accelerometer_tilt_angle.cpp
)
set(headers
    ${headers_dir}/accelerometer.hpp
    ${headers_dir}/accelerometer_exception.hpp
    ${headers_dir}/accelerometer_tilt_angle.hpp
)

add_library(${project_name} STATIC ${sources} ${headers})

set_target_properties(${project_name} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

target_include_directories(${project_name} PUBLIC ${robarm_dir})

target_link_libraries(${project_name} LINK_PUBLIC
    robarm_hal_i2c
    robarm_utils_common
)
