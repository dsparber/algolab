#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Value
struct value {
  int cost;
  int numBeverages;
  bool usesBeverage;

  // "lexicographic" order with the following priorities:
  // 1. Cheapest
  // 2. Highest number of beverages
  // 3. Not needing to take the drink
  bool operator>(value v) {
    return cost < v.cost || 
      (cost == v.cost && numBeverages > v.numBeverages) ||
      (cost == v.cost && numBeverages == v.numBeverages && !usesBeverage && v.usesBeverage);
  }
};


// Super similar to the knapsack problem
// => Solve with DP
void solve()
{
  int n, k;
  cin >> n >> k;

  // Read costs and volumes
  vector<int> c(n);
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i] >> v[i];
  }


  // Initialize DP
  // row i: all beverages up to i available
  // col j: at least j liters needed  
  vector<vector<value>> dp(n, vector<value>(k + 1));
  for (int i = 1; i < n; ++i) {
    dp[i][0] = {0, 0, false};
  }
  for (int j = 1; j <= k; ++j) {
    int cost = c[0] * int(ceil(1. * j / v[0]));
    dp[0][j] = {cost, 1, true};
  }

  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= k; ++j) {
      // Value with i - 1 beverages
      value valueWithout = dp[i - 1][j];
      valueWithout.usesBeverage = false;
      // Value with beverage i
      value valueWith = {c[i], 1, true};
      // More than one bottle needed
      if (j > v[i]) { 
        valueWith.cost += dp[i][j - v[i]].cost;
        valueWith.numBeverages = dp[i][j - v[i]].numBeverages;
        if (!dp[i][j - v[i]].usesBeverage) {
          valueWith.numBeverages += 1;
        }
      }

      // What is better?
      if (valueWithout > valueWith) {
        dp[i][j] = valueWithout;
      }
      else {
        dp[i][j] = valueWith;
      }
    }
  }

  // Print solution
  cout << dp[n - 1][k].cost << " " << dp[n - 1][k].numBeverages << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}