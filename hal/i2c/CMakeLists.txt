# Copyright (c) 2023 Robarm
# All rights reserved

set(project_name robarm_hal_i2c)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)
set(headers_dir ${CMAKE_CURRENT_LIST_DIR}/include)

set(sources
    ${sources_dir}/i2c_component.cpp
    ${sources_dir}/i2c_peripheral.cpp
)
set(headers
    ${headers_dir}/i2c_component.hpp
    ${headers_dir}/i2c_peripheral.hpp
)

add_library(${project_name} STATIC ${sources} ${headers})

set_target_properties(${project_name} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

target_include_directories(${project_name} PUBLIC ${robarm_dir})
