cmake_minimum_required(VERSION 3.25)
project(ctg)

include_directories(include)
add_executable(${PROJECT_NAME} src/main.cpp src/CellurarGenerator.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-window)