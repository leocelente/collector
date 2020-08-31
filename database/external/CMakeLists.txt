include(FetchContent)

# ------------------------------------------------------------------------------
# A modern, C++-native, header-only, test framework for unit-tests,
# TDD and BDD - using C++11, C++14, C++17 and later
FetchContent_Declare(
  extern_leveldb

  GIT_REPOSITORY https://github.com/google/leveldb.git
  GIT_TAG        1.22)

FetchContent_GetProperties(extern_leveldb)
if(NOT extern_leveldb_POPULATED)
  FetchContent_Populate(extern_leveldb)
  add_subdirectory(
    ${extern_leveldb_SOURCE_DIR}
    ${extern_leveldb_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()

