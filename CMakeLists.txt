cmake_minimum_required(VERSION 3.12.0)
project(gbmu VERSION 0.1.0)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

Set(SPDLOG_BUILD_TESTING OFF)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "deps/sfml/")
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

add_subdirectory(deps/spdlog)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fexceptions -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBRARIES spdlog)

target_include_directories(${PROJECT_NAME}
    PUBLIC deps/tclap/include
    PUBLIC deps/spdlog/include
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
