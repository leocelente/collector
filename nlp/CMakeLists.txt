cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(nlp)
include("external/mitielib/cmake")

add_library(
    nlp
    "include/nlp.h"
    "src/nlp.cpp" 
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set(mitie_include_path "${mitie_path}include" PARENT_SCOPE)
target_link_libraries(nlp PUBLIC mitie)
