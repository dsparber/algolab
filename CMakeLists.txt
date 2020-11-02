cmake_minimum_required(VERSION 3.16)
project(algolab)

set(CMAKE_CXX_STANDARD 14)

find_package(CGAL)

add_executable(07_maximizeit src/week7/maximizeit.cpp)
target_link_libraries(07_maximizeit CGAL::CGAL)

add_executable(07_diet src/week7/diet.cpp)
target_link_libraries(07_diet CGAL::CGAL)

add_executable(07_inball src/week7/inball.cpp)
target_link_libraries(07_inball CGAL::CGAL)

add_executable(07_radiation src/week7/radiation.cpp)
target_link_libraries(07_radiation CGAL::CGAL)

add_executable(pow02_deck_of_cards src/pow/pow02_deck_of_cards.cpp)
add_executable(pow03_russia src/pow/pow03_russia_official_solution.cpp)
add_executable(pow04_defensive_line src/pow/pow04_defensive_line.cpp)
add_executable(pow05_motorcycles src/pow/pow05_motorcycles.cpp)
add_executable(pow06_tracking src/pow/pow06_tracking.cpp)
add_executable(pow07_octopussy src/pow/pow07_octopussy.cpp)
add_executable(pow08_surveillance src/pow/pow08_surveillance.cpp)

target_link_libraries(pow05_motorcycles CGAL::CGAL)