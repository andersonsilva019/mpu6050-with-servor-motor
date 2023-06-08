# Copyright (c) 2023 Robarm
# All rights reserved

set(project_name robarm_utils_logger)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)
set(headers_dir ${CMAKE_CURRENT_LIST_DIR}/include)

set(headers
    ${headers_dir}/logger.hpp
)

add_library(${project_name} STATIC ${sources} ${headers})

set_target_properties(${project_name} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

target_include_directories(${project_name} PUBLIC ${robarm_dir})
