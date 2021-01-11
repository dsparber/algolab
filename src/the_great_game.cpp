#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

int winner(int r, int b, int n, int counter, vector<std::vector<int>> &neighbors, map<int, map<int, map<int, int>>> &memo) {
  counter = counter % 4;
  if (r == n - 1) {
    return 0; // Sherlock
  }
  if (b == n - 1) {
    return 1; // Moriarty
  }
  if (memo.find(r) != memo.end() && memo[r].find(b) != memo[r].end() && memo[r][b].find(counter) != memo[r][b].end()) {
    return memo[r][b][counter];
  }

  int player = counter % 2;
  bool moveRed = ((counter / 2) + player) % 2 == 0;
  int current = moveRed ? r : b;

  bool playerWins = false;;
  for (int neighbor : neighbors[current]) {
     int newR = r, newB = b;
     if (moveRed) {
       newR = neighbor;
     }
     else {
       newB = neighbor;
     }
     int winnerForNeighbor = winner(newR, newB, n, counter + 1, neighbors, memo);
     if (winnerForNeighbor == player) {
       playerWins = true;
       break;
     }

  }
  int winningPlayer = playerWins ? player : (player + 1) % 2;

  memo[r][b][counter] = winningPlayer;
  return winningPlayer;
}

int solve() {
  int n; std::cin >> n;
  int m; std::cin >> m;
  int r; std::cin >> r; r = r - 1;
  int b; std::cin >> b; b = b - 1;
  vector<vector<int>> neighbors(n, vector<int>());
  int u, v;
  for (int i = 0; i < m; ++i) {
    cin >> u;
    cin >> v;
    // u,v are in range [1...n], transform to [0...n-1]
    neighbors[u - 1].push_back(v - 1);
  }
  
  //vector<vector<vector<int>>> memo(n, vector<vector<int>>(n, vector<int>(n, -1)));
  map<int, map<int, map<int, int>>> memo;
  int result = winner(r, b, n, 0, neighbors, memo);
  return result;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    int solution = solve();
    std::cout << solution << std::endl;
  }
}