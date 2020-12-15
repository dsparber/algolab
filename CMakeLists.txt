cmake_minimum_required(VERSION 3.16)
project(algolab)

set(CMAKE_CXX_STANDARD 14)

find_package(CGAL)


add_executable(maximizeit src/maximizeit.cpp)
add_executable(diet src/diet.cpp)
add_executable(inball src/inball.cpp)
add_executable(radiation src/radiation.cpp)

target_link_libraries(maximizeit CGAL::CGAL)
target_link_libraries(diet CGAL::CGAL)
target_link_libraries(inball CGAL::CGAL)
target_link_libraries(radiation CGAL::CGAL)


add_executable(bistro src/bistro.cpp)
add_executable(germs src/germs.cpp)
add_executable(h1n1 src/h1n1.cpp)
add_executable(clues src/clues.cpp)

target_link_libraries(bistro CGAL::CGAL)
target_link_libraries(germs CGAL::CGAL)
target_link_libraries(h1n1 CGAL::CGAL)
target_link_libraries(clues CGAL::CGAL)


add_executable(real_estate src/real_estate.cpp)
add_executable(placing_knights src/placing_knights.cpp)
add_executable(algocoon src/algocoon.cpp)
add_executable(casino src/casino.cpp)


add_executable(chariot_race src/chariot_race.cpp)
add_executable(switzerland src/switzerland.cpp)
add_executable(new_york src/new_york.cpp)
add_executable(worldcup src/worldcup.cpp)

target_link_libraries(worldcup CGAL::CGAL)

add_executable(return_of_the_jedi src/return_of_the_jedi.cpp)
add_executable(lestrade src/lestrade.cpp)
add_executable(hand src/hand.cpp)


add_executable(moving_books src/moving_books.cpp)


target_link_libraries(lestrade CGAL::CGAL)

add_executable(deck_of_cards src/deck_of_cards.cpp)
add_executable(russia src/russia_official_solution.cpp)
add_executable(defensive_line src/defensive_line.cpp)
add_executable(motorcycles src/motorcycles.cpp)
add_executable(tracking src/tracking.cpp)
add_executable(octopussy src/octopussy.cpp)
add_executable(surveillance src/surveillance.cpp)
add_executable(legions src/legions.cpp)
add_executable(idefix src/idefix.cpp)
add_executable(fleetrace src/fleetrace.cpp)
add_executable(iron_islands src/iron_islands.cpp)

target_link_libraries(motorcycles CGAL::CGAL)
target_link_libraries(legions CGAL::CGAL)
target_link_libraries(idefix CGAL::CGAL)