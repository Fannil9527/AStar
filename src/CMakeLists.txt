project(main)

add_subdirectory(strategy)
add_subdirectory(grad_map)
add_subdirectory(show_result)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
PUBLIC
${Strategy_Dir}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
strategy
)

target_include_directories(${PROJECT_NAME}
PUBLIC
${Show_Result_Dir}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
show_result
)