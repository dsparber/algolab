cmake_minimum_required(VERSION 3.16)
project(algolab)

set(CMAKE_CXX_STANDARD 14)

find_package(CGAL)


add_executable(07_maximizeit src/week7/maximizeit.cpp)
add_executable(07_diet src/week7/diet.cpp)
add_executable(07_inball src/week7/inball.cpp)
add_executable(07_radiation src/week7/radiation.cpp)

target_link_libraries(07_maximizeit CGAL::CGAL)
target_link_libraries(07_diet CGAL::CGAL)
target_link_libraries(07_inball CGAL::CGAL)
target_link_libraries(07_radiation CGAL::CGAL)


add_executable(08_bistro src/week8/bistro.cpp)
add_executable(08_germs src/week8/germs.cpp)
add_executable(08_h1n1 src/week8/h1n1.cpp)
add_executable(08_clues src/week8/clues.cpp)

target_link_libraries(08_bistro CGAL::CGAL)
target_link_libraries(08_germs CGAL::CGAL)
target_link_libraries(08_h1n1 CGAL::CGAL)
target_link_libraries(08_clues CGAL::CGAL)


add_executable(09_real_estate src/week9/real_estate.cpp)
add_executable(09_placing_knights src/week9/placing_knights.cpp)
add_executable(09_algocoon src/week9/algocoon.cpp)
add_executable(09_casino src/week9/casino.cpp)


add_executable(10_chariot_race src/week10/chariot_race.cpp)


add_executable(pow02_deck_of_cards src/pow/pow02_deck_of_cards.cpp)
add_executable(pow03_russia src/pow/pow03_russia_official_solution.cpp)
add_executable(pow04_defensive_line src/pow/pow04_defensive_line.cpp)
add_executable(pow05_motorcycles src/pow/pow05_motorcycles.cpp)
add_executable(pow06_tracking src/pow/pow06_tracking.cpp)
add_executable(pow07_octopussy src/pow/pow07_octopussy.cpp)
add_executable(pow08_surveillance src/pow/pow08_surveillance.cpp)
add_executable(pow09_legions src/pow/pow09_legions.cpp)
add_executable(pow10_idefix src/pow/pow10_idefix.cpp)

target_link_libraries(pow05_motorcycles CGAL::CGAL)
target_link_libraries(pow10_idefix CGAL::CGAL)