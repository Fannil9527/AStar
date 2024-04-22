project(grad_map)

add_library(${PROJECT_NAME}
SHARED
grad_map.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
${Config_Dir}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
easyx
)