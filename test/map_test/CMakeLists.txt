project(map_test)

add_executable(${PROJECT_NAME} map_test.cpp)

target_include_directories(${PROJECT_NAME}
PUBLIC
${Grad_Map_Dir}
)

target_include_directories(${PROJECT_NAME}
PUBLIC
${Config_Dir}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
grad_map
)

add_test(
    NAME map_info_test
    COMMAND ${PROJECT_NAME}
)