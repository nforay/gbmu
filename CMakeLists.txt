cmake_minimum_required(VERSION 3.2.0)
project(gbmu VERSION "0.1.0")
configure_file(include/config.h.in include/config.h @ONLY)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_BUILD_TYPE Debug)
Set(BUILD_SHARED_LIBS OFF)
Set(SPDLOG_BUILD_SHARED OFF)

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
#find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory(deps/sfml)
add_subdirectory(deps/spdlog)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fexceptions -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/deps/spdlog/include"
    "${PROJECT_SOURCE_DIR}/deps/tclap/include"
)

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBRARIES
    spdlog
    sfml-audio
    sfml-graphics
    sfml-window
    sfml-system
    #Qt6::Widgets
)

target_include_directories(${PROJECT_NAME}
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})
