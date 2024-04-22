project(strategy)

add_library(${PROJECT_NAME}
SHARED
strategy.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
${Grad_Map_Dir}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
grad_map
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
Eigen3::Eigen
)
