cmake_minimum_required(VERSION 3.00)
project(project_name CXX)
set(CMAKE_CXX_STANDARD 20)
include_directories(HEADER_FILES)
file(GLOB UNIT
    "unit_testy.cpp"
    )
    add_executable(unit_testy ${UNIT})
file(GLOB TREE
    "test_drzewa.cpp"
    )
    add_executable(testy_drzewa ${TREE})
file(GLOB TEST
    "testy_czasowe.cpp"
    )
    add_executable(testy_czasowe ${TEST})
