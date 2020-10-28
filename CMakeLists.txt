cmake_minimum_required(VERSION 3.16)
project(algolab)

set(CMAKE_CXX_STANDARD 14)

find_package(CGAL)

add_executable(07_maximizeit src/week7/maximizeit.cpp)
target_link_libraries(07_maximizeit CGAL::CGAL)

add_executable(07_diet src/week7/diet.cpp)
target_link_libraries(07_diet CGAL::CGAL)