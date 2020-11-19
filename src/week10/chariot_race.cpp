#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;


// Cost of the subtree
struct cost {
  // Root (of subtree) selected 
  int selected; 
  // Parent is selected, i.e. root is already covered
  int covered; 
  // Parent is not selected, at least one child needs to be selected to cover root
  int notCovered; 
};


cost calculateCost(int u, vector<int> &costs, vector<vector<int>> &neighbors) {

  // Leaf node: just cost of leaf if selected, if not covered, we must select leaf
  if (neighbors[u].size() == 0) {
    return {costs[u], 0, costs[u]};
  }
  
  cost current = {costs[u], 0, 0};
  int bestDiff = numeric_limits<int>::max(); 
  for (auto v : neighbors[u]) {
    auto costV = calculateCost(v, costs, neighbors);
    current.selected += costV.covered;
    current.covered += costV.notCovered;
    bestDiff = min(bestDiff, costV.selected - costV.notCovered);
  }
  
  // Best we can do when we need to select one child
  current.notCovered = current.covered + bestDiff;
  
  // It can never be more expensive than selecting the vertex
  current.covered = min(current.selected, current.covered);
  current.notCovered = min(current.selected, current.notCovered);
  
  return current;
}


// Important observation:
// A connected graph with n-1 edges is a tree
// The root of the tree will always be vertex 0
void solve() {
  int n; cin >> n;
  
  vector<vector<int>> neighbors(n, vector<int>());
  int u, v;
  for (int i = 0; i < n - 1; ++i) {
    cin >> u >> v;
    neighbors[u].push_back(v);
  }
  vector<int> costs(n);
  for (int i = 0; i < n; ++i) {
    cin >> costs[i];
  }
  
  cost total = calculateCost(0, costs, neighbors);
  cout << total.notCovered << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
