cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(database)
add_subdirectory(external)

add_library(
    database
    "include/database.h"
    "src/database.cpp"
    "include/url_db.h"
    "src/url_db.cpp"
    "include/inverted_index.h"
    "src/inverted_index.cpp"   
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(database PUBLIC leveldb)
