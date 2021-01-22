#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct edge {
  int v;
  int p;
};

void solve() {
  int n; cin >> n;
  int m; cin >> m;
  long x; cin >> x;
  int k; cin >> k;
  
  vector<vector<edge>> neighbors(n, vector<edge>());
  
  int u, v, p;
  for (int i = 0; i < m; ++i) {
    cin >> u;
    cin >> v;
    cin >> p;
    neighbors[u].push_back(edge({v, p}));
  }
  
  for (int u = 0; u < n; ++u) {
    if (neighbors[u].size() == 0) {
      for (unsigned int j = 0; j < neighbors[0].size(); ++j) {
        neighbors[u].push_back(neighbors[0][j]);
      }
    }
  }
  
  vector<long> dp(n, -1);
  dp[0] = 0;
  
  int kMin = -1;
  for (int i = 0; i < k; ++i) {
    vector<long> dpNew(n, -1);
    
    for (int u = 0; u < n; ++u) {
      if (dp[u] != -1) {
        for (unsigned int j = 0; j < neighbors[u].size(); ++j) {
          auto e = neighbors[u][j];
          dpNew[e.v] = max(dpNew[e.v], dp[u] + e.p);
          if (dpNew[e.v] >= x && kMin == -1) {
            kMin = i;
            break;
          }
        }
      }
    }
    
    dp = dpNew;
  }
  if (kMin == -1) {
    cout << "Impossible" << endl;
  } else {
    cout << kMin + 1 << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}