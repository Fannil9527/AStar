project(main)

add_subdirectory(strategy)
add_subdirectory(grad_map)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
PUBLIC
${Strategy_Dir}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
strategy
)
