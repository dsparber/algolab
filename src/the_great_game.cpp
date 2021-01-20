#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;


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

  vector<int> minSteps(n, numeric_limits<int>::max());
  vector<int> maxSteps(n, -1);

  minSteps[n - 1] = 0;
  maxSteps[n - 1] = 0;

  for (int u = n - 2; u >= 0; --u) {
    for (int v : neighbors[u]) {
      minSteps[u] = min(maxSteps[v] + 1, minSteps[u]);
      maxSteps[u] = max(minSteps[v] + 1, maxSteps[u]);
    }
  }

  if (minSteps[r] < minSteps[b]) {
    return 0;
  }

  if (minSteps[r] > minSteps[b]) {
    return 1;
  }

  if (minSteps[r] % 2 == 1) {
    return 0; 
  }

  return 1;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    int solution = solve();
    std::cout << solution << std::endl;
  }
}