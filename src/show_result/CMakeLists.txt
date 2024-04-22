project(show_result)

add_library(${PROJECT_NAME}
SHARED
show_result.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
${Strategy_Dir}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
strategy
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
easyx
)