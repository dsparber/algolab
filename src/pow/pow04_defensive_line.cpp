#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void solve() {
  int n, m, k;
  cin >> n;
  cin >> m;
  cin >> k;
  
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  vector<int> sum(n + 1);
  sum[0] = 0;
  for (int i = 0; i < n; ++i) {
    sum[i + 1] = v[i] + sum[i];
  }
  
  // Sliding window to get a, b with sum = k
  
  int a = 0; 
  int b = 0;
  vector<int> startOfIntervall(n + 1, -1);
  
  while (a <= n && b <= n) {
    if (sum[b] - sum[a] == k) {
      startOfIntervall[b] = a;
    }
    
    // Sum would be to large if we were to move b, thus move a
    if (sum[b + 1] - sum[a] > k) {
      ++a;
    }
    else {
      ++b;
    }
  }
  
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

  for (int attackers = 1; attackers <= m; ++attackers) { 
    dp[attackers][0] = -1;
    for (int i = 1; i <= n; ++i) {
      int i0 = startOfIntervall[i];
      if (attackers == 1) {
        int newValue = (i0 == -1) ? -1 : (i - i0);
        dp[attackers][i] = max(dp[attackers][i - 1], newValue);
      }
      else {
        int newValue = -1;
        if (i0 != -1 && dp[attackers - 1][i0] != -1) {
          newValue = i - i0;
          newValue += dp[attackers - 1][i0];
        }
        dp[attackers][i] = max(dp[attackers][i - 1], newValue);
      }
    }
  }
  
  /*
  for (int row = 1; row <= m; ++row) {
    for (int col = 1; col <= n; ++col) {
      cout << dp[row][col] << " ";
    }
    cout << endl;
  }
  cout << endl;
  */
  
  if (dp[m][n] == -1) {
    cout << "fail" << endl;
  } else {
    cout << dp[m][n] << endl;
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
} 