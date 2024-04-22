cmake_minimum_required(VERSION 3.29.0)
project(planning
    VERSION 0.0.1
    DESCRIPTION "a demo of cmake planning"
    HOMEPAGE_URL "https://github.com/Fannil9527/AStar.git"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

#set value
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(Config_Dir ${CMAKE_SOURCE_DIR}/src/config)
set(Strategy_Dir ${CMAKE_SOURCE_DIR}/src/strategy)
set(Grad_Map_Dir ${CMAKE_SOURCE_DIR}/src/grad_map)
set(Show_Result_Dir ${CMAKE_SOURCE_DIR}/src/show_result)
set(Main_Dir ${CMAKE_SOURCE_DIR}/src/main)

#third party lib
set(EIGEN3_INCLUDE_DIR "C:/Program Files/eigen-3.4.0")
list(APPEND CMAKE_MODULE_PATH "${EIGEN3_INCLUDE_DIR}/cmake")
message("CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

find_package(Eigen3 3.4 REQUIRED)
if(TARGET Eigen3::Eigen)
    message(STATUS "******** Eigen3 3.4 found in ${EIGEN3_INCLUDE_DIR} *******")
endif()

#add sub directory
add_subdirectory(src)
add_subdirectory(test/map_test)