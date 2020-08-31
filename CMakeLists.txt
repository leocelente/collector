cmake_minimum_required(VERSION 3.11)

project(thecollector)

add_subdirectory("database")
add_subdirectory("nlp")

add_executable(
    ${PROJECT_NAME}
    collector/include/collector.h
    collector/src/collector.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

include_directories("${PROJECT_SOURCE_DIR}/database/include")
include_directories("${PROJECT_SOURCE_DIR}/nlp/include")


target_link_libraries(${PROJECT_NAME} PRIVATE database)
target_link_libraries(${PROJECT_NAME} PRIVATE nlp)
