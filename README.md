# Algorithms Lab 2020

## Build

```shell script
mkdir build
cd build
cmake ..
make -j8
```

## Problems

| Task                                                  | Implementation                                            | Score     | Week      | Topics        | 
| ----------------------------------------------------- | --------------------------------------------------------- | --------- | --------- | ------------- |
| [Build the Sum](tasks/build_the_sum.pdf)              | [build_the_sum.cpp](src/build_the_sum.cpp)                | 100       | Week 1    | ---           |
| [Dominoes](tasks/dominoes.pdf)                        | [dominoes.cpp](src/dominoes.cpp)                          | 100       | Week 1    | ---           |
| [Even pairs](tasks/deck_of_cards.pdf)                 | [even_pairs.cpp](src/even_pairs.cpp)                      | 100       | Week 1    | ---           |
| [Even Matrices](tasks/even_matrices.pdf)              | [even_matrices.cpp](src/even_matrices.cpp)                | 100       | Week 1    | ---           |
| [Deck of Cards](tasks/deck_of_cards.pdf)              | [deck_of_cards.cpp](src/deck_of_cards.cpp)                | 100       | Week 2*   | DP            |
| [Burning Coins](tasks/burning_coins.pdf)              | [burning_coins.cpp](src/burning_coins.cpp)                | 100       | Week 2    | DP            |
| [The Great Game](tasks/the_great_game.pdf)            | [the_great_game.cpp](src/the_great_game.cpp)              | 100       | Week 2    | DP            |
| [Beach Bars](tasks/beach_bars.pdf)                    | [beach_bars.cpp](src/beach_bars.cpp)                      | 100       | Week 2    | SW            |
| [Search Snippets](tasks/search_snippets.pdf)          | [search_snippets.cpp](src/search_snippets.cpp)            | 100       | Week 2    | SW            |
| [Russia](tasks/russia.pdf)                            | [russia.cpp](src/russia_official_solution.cpp)            | 100       | Week 3*   | DP            |
| [Hit](tasks/hit.pdf)                                  | [hit.cpp](src/hit.cpp)                                    | 100       | Week 3    | Geo           |
| [First Hit](tasks/first_hit.pdf)                      | [first_hit.cpp](src/first_hit.cpp)                        | 100       | Week 3    | Geo           |
| [Antenna](tasks/antenna.pdf)                          | [antenna.cpp](src/antenna.cpp)                            | 100       | Week 3    | Geo           |
| [Hiking Maps](tasks/hiking_maps.pdf)                  | [hiking_maps.cpp](src/hiking_maps.cpp)                    | 100       | Week 3    | Geo           |
| [Defensive Line](tasks/defensive_line.pdf)            | [defensive_line.cpp](src/defensive_line.cpp)              | 100       | Week 4*   | SW & DP       |
| [First Steps with BGL](tasks/first_steps.pdf)         | [first_steps.cpp](src/first_steps.cpp)                    | 100       | Week 4    | SP            |
| [Ant Challenge](tasks/ant_challenge.pdf)              | [ant_challenge.cpp](src/ant_challenge.cpp)                | 100       | Week 4    | MST & SP      |
| [Buddy Selection](tasks/buddy_selection.pdf)          | [buddy_selection.cpp](src/buddy_selection.cpp)            | 100       | Week 4    | MM            |
| [Important Bridges](tasks/important_bridges.pdf)      | [important_bridges.cpp](src/important_bridges.cpp)        | 100       | Week 4    | 2CC           |
| [Motorcycles](tasks/motorcycles.pdf)                  | [motorcycles.cpp](src/motorcycles.cpp)                    | 100       | Week 5*   | Geo           |
| [Boats](tasks/boats.pdf)                              | [boats.cpp](src/boats.cpp)                                | 100       | Week 5    | Greedy        |
| [Attack of the Clones](tasks/attack_of_the_clones.pdf)| [attack_of_the_clones.cpp](src/attack_of_the_clones.cpp)  | 100       | Week 5    | Greedy        |
| [San Francisco](tasks/san_francisco.pdf)              | [san_francisco.cpp](src/san_francisco.cpp)                | 100       | Week 5    | DP            |
| [Asterix the Gaul](tasks/asterix_the_gaul.pdf)        | [asterix_the_gaul.cpp](src/asterix_the_gaul.cpp)          | 100       | Week 5    | BS & SL       |
| [Tracking](tasks/tracking.pdf)                        | [tracking.cpp](src/tracking.cpp)                          | 100       | Week 6*   | SP            |
| [Shopping Trip](tasks/shopping_trip.pdf)              | [shopping_trip.cpp](src/shopping_trip.cpp)                | 100       | Week 6    | MF            |
| [Knights](tasks/knights.pdf)                          | [knights.cpp](src/knights.cpp)                            | 100       | Week 6    | MF            |
| [Tiles](tasks/tiles.pdf)                              | [tiles.cpp](src/tiles.cpp)                                | 100       | Week 6    | MF            |
| [Kingdom Defence](tasks/kingdom_defence.pdf)          | [kingdom_defence.cpp](src/kingdom_defence.cpp)            | 100       | Week 6    | MF            |
| [Octopussy](tasks/octopussy.pdf)                      | [octopussy.cpp](src/octopussy.cpp)                        | 100       | Week 7*   | DP-like       |
| [Maximize it](tasks/maximizeit.pdf)                   | [maximizeit.cpp](src/maximizeit.cpp)                      | 100       | Week 7    | LP            | 
| [Diet](tasks/diet.pdf)                                | [diet.cpp](src/diet.cpp)                                  | 100       | Week 7    | LP            | 
| [Inball](tasks/inball.pdf)                            | [inball.cpp](src/inball.cpp)                              | 100       | Week 7    | LP            | 
| [Radiation](tasks/radiation.pdf)                      | [radiation.cpp](src/radiation.cpp)                        | 100       | Week 7    | LP            | 
| [Surveillance](tasks/surveillance.pdf)                | [surveillance.cpp](src/surveillance.cpp)                  | 100       | Week 8*   | MF            |
| [Bistro](tasks/bistro.pdf)                            | [bistro.cpp](src/bistro.cpp)                              | 100       | Week 8    | DT            | 
| [Germs](tasks/germs.pdf)                              | [germs.cpp](src/germs.cpp)                                | 100       | Week 8    | DT            | 
| [H1N1](tasks/h1n1.pdf)                                | [h1n1.cpp](src/h1n1.cpp)                                  | 100       | Week 8    | DT, MST       | 
| [Clues](tasks/clues.pdf)                              | [clues.cpp](src/clues.cpp)                                | 100       | Week 8    | DT, 2C, CC    | 
| [Legions](tasks/legions.pdf)                          | [legions.cpp](src/legions.cpp)                            | 100       | Week 9*   | LP            |
| [Casino Royale](tasks/casino.pdf)                     | [casino.cpp](src/casino.cpp)                              | 100       | Week 9    | MCMF          |
| [Real Estate](tasks/real_estate.pdf)                  | [real_estate.cpp](src/real_estate.cpp)                    | 100       | Week 9    | MCMF          |
| [Algocoon](tasks/algocoon.pdf)                        | [algocoon.cpp](src/algocoon.cpp)                          | 100       | Week 9    | MC            |
| [Placing Knights](tasks/placing_knights.pdf)          | [placing_knights.cpp](src/placing_knights.cpp)            | 100       | Week 9    | MaxIS         |
| [Idefix](tasks/idefix.pdf)                            | [idefix.cpp](src/idefix.cpp)                              | 100       | Week 10*  | DT & UF       |
| [Chariot Race](tasks/chariot_race.pdf)                | [chariot_race.cpp](src/chariot_race.cpp)                  | 100       | Week 10   | DP-like       |
| [New York](tasks/new_york.pdf)                        | [new_york.cpp](src/new_york.cpp)                          | 100       | Week 10   | SW over tree  |
| [Worldcup](tasks/worldcup.pdf)                        | [worldcup.cpp](src/worldcup.cpp)                          | 100       | Week 10   | LP & DT       |
| [Switzerland](tasks/switzerland.pdf)                  | [switzerland.cpp](src/switzerland.cpp)                    | 100       | Week 10   | MF            |
| [Fleet Race](tasks/fleetrace.pdf)                     | [fleetrace.cpp](src/fleetrace.cpp)                        | 100       | Week 11*  | MCMF          |
| [Return of the Jedi](tasks/return_of_the_jedi.pdf)    | [return_of_the_jedi.cpp](src/return_of_the_jedi.cpp)      | 100       | Week 11   | 2nd best MST  |
| [Lestrade](tasks/lestrade.pdf)                        | [lestrade.cpp](src/lestrade.cpp)                          | 100       | Week 11   | LP & DT       |
| [Hand](tasks/hand.pdf)                                | [hand.cpp](src/hand.cpp)                                  | 100       | Week 11   | DT, UF        |
| [Meereen](tasks/meereen.pdf)                          | [meereen.cpp](src/meereen.cpp)                            | 100       | Week 11   | DP            |
| [Iron Islands](tasks/iron_islands.pdf)                | [iron_islands.cpp](src/iron_islands.cpp)                  | 100       | Week 12*  | SW            |
| [Car Sharing](tasks/carsharing.pdf)                   | [carsharing.cpp](src/carsharing.cpp)                      | 100       | Week 12   | MCMF          |
| [Hong Kong](tasks/hongkong.pdf)                       | [hongkong.cpp](src/hongkong.cpp)                          | 100       | Week 12   | DT, SP        |
| [India](tasks/india.pdf)                              | [india.cpp](src/india.cpp)                                | 100       | Week 12   | BS & MCMF     |
| [Moving Books](tasks/moving_books.pdf)                | [moving_books.cpp](src/moving_books.cpp)                  | 100       | Week 12   | Greedy        |
| [Lannister](tasks/lannister.pdf)                      | [lannister.cpp](src/lannister.cpp)                        | 100       | Week 13*  | LP            |
| [Evolution](tasks/evolution.pdf)                      | [evolution.cpp](src/evolution.cpp)                        | 100       | Week 13   | DFS & BS      |
| [Marathon](tasks/marathon.pdf)                        | [marathon.cpp](src/marathon.cpp)                          | 100       | Week 13   | SP & MF       |
| [Punch](tasks/punch.pdf)                              | [punch.cpp](src/punch.cpp)                                | 100       | Week 13   | DP            |
| [Sith](tasks/sith.pdf)                                | [sith.cpp](src/sith.cpp)                                  | 100       | Week 13   | DT & BS       |
| [Secret Service](tasks/secret_service.pdf)            | [secret_service.cpp](src/secret_service.cpp)              | 100       | Week 14*  | BS & MF       |


### Legend
- *: This was a "Problem of the Week"
- 2C: 2-Coloring / Bipartition
- 2CC: 2-Connected Components / Biconnected Components
- BS: Binary Search
- CC: Connected Components
- DFS: Depth First Search
- DP: Dynamic Programming
- DT: Delaunay Triangulation
- Geo: Geometric
- LP: Linear Programming
- MC: Min. Cut
- MCMF: Min. Cost Max. Flow
- MF: Max. Flow
- MM: Maximal Matching
- MST: Minimum Spanning Tree
- SL: Split & List
- SP: Shortest Path
- SW: Sliding Window
- UF: Union Find

## Official Solutions

For some problems, an [official solutions](official_solutions) was released. You can find them in this repository as well.
