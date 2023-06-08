# Copyright (c) 2023 Robarm
# All rights reserved

set(project_name robarm_hal_device)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)
set(headers_dir ${CMAKE_CURRENT_LIST_DIR}/include)

set(sources
    ${sources_dir}/linux_device.cpp
    ${sources_dir}/linux_device_access.cpp
    ${sources_dir}/linux_device_exception.cpp
)
set(headers
    ${headers_dir}/linux_device.hpp
    ${headers_dir}/linux_device_access.hpp
    ${headers_dir}/linux_device_exception.hpp
)

add_library(${project_name} STATIC ${sources} ${headers})

set_target_properties(${project_name} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

target_include_directories(${project_name} PUBLIC ${robarm_dir})

target_link_libraries(${project_name} LINK_PUBLIC
    robarm_utils_common
)
