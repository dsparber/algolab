cmake_minimum_required(VERSION 3.16)
project(algolab)

set(CMAKE_CXX_STANDARD 14)

find_package(CGAL)

# Week 1
add_executable(build_the_sum src/build_the_sum.cpp)
add_executable(dominoes src/dominoes.cpp)
add_executable(even_pairs src/even_pairs.cpp)
add_executable(even_matrices src/even_matrices.cpp)


# Week 2
add_executable(burning_coins src/burning_coins.cpp)
add_executable(the_great_game src/the_great_game.cpp)
add_executable(beach_bars src/beach_bars.cpp)
add_executable(search_snippets src/search_snippets.cpp)


# Week 2
add_executable(ant_challenge src/ant_challenge.cpp)
add_executable(important_bridges src/important_bridges.cpp)
add_executable(first_steps src/first_steps.cpp)
add_executable(buddy_selection src/buddy_selection.cpp)


# Week 3
add_executable(hit src/hit.cpp)
add_executable(first_hit src/first_hit.cpp)
add_executable(antenna src/antenna.cpp)
add_executable(hiking_maps src/hiking_maps.cpp)


# Week 4
add_executable(attack_of_the_clones src/attack_of_the_clones.cpp)
add_executable(san_francisco src/san_francisco.cpp)
add_executable(boats src/boats.cpp)
add_executable(asterix_the_gaul src/asterix_the_gaul.cpp)


# Week 7
add_executable(maximizeit src/maximizeit.cpp)
add_executable(diet src/diet.cpp)
add_executable(inball src/inball.cpp)
add_executable(radiation src/radiation.cpp)

target_link_libraries(maximizeit CGAL::CGAL)
target_link_libraries(diet CGAL::CGAL)
target_link_libraries(inball CGAL::CGAL)
target_link_libraries(radiation CGAL::CGAL)


# Week 8
add_executable(bistro src/bistro.cpp)
add_executable(germs src/germs.cpp)
add_executable(h1n1 src/h1n1.cpp)
add_executable(clues src/clues.cpp)

target_link_libraries(bistro CGAL::CGAL)
target_link_libraries(germs CGAL::CGAL)
target_link_libraries(h1n1 CGAL::CGAL)
target_link_libraries(clues CGAL::CGAL)


# Week 9
add_executable(real_estate src/real_estate.cpp)
add_executable(placing_knights src/placing_knights.cpp)
add_executable(algocoon src/algocoon.cpp)
add_executable(casino src/casino.cpp)


# Week 10
add_executable(chariot_race src/chariot_race.cpp)
add_executable(switzerland src/switzerland.cpp)
add_executable(new_york src/new_york.cpp)
add_executable(worldcup src/worldcup.cpp)

target_link_libraries(worldcup CGAL::CGAL)


# Week 11
add_executable(return_of_the_jedi src/return_of_the_jedi.cpp)
add_executable(lestrade src/lestrade.cpp)
add_executable(hand src/hand.cpp)
add_executable(meereen src/meereen.cpp)

target_link_libraries(lestrade CGAL::CGAL)


# Week 12
add_executable(moving_books src/moving_books.cpp)
add_executable(carsharing src/carsharing.cpp)
add_executable(india src/india.cpp)
add_executable(hongkong src/hongkong.cpp)

target_link_libraries(hongkong CGAL::CGAL)


# Week 13
add_executable(evolution src/evolution.cpp)
add_executable(marathon src/marathon.cpp)
add_executable(punch src/punch.cpp)
add_executable(sith src/sith.cpp)

target_link_libraries(sith CGAL::CGAL)


# Problems of the week
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
add_executable(lannister src/lannister.cpp)
add_executable(secret_service src/secret_service.cpp)

target_link_libraries(motorcycles CGAL::CGAL)
target_link_libraries(legions CGAL::CGAL)
target_link_libraries(idefix CGAL::CGAL)