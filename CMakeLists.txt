cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME dungeon)
project(${PROJECT_NAME}) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

file(GLOB HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES src/*.cpp)
add_library(dungeon_object STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

enable_testing()
add_subdirectory(external)
add_subdirectory(tests)
add_dependencies(${PROJECT_NAME} run_tests)