#include <iostream>
#include <vector>
#include <cmath>

int solve() {
  int n; std::cin >> n;
  std::vector<int> v;
  int vi;
  std::vector<std::vector<int>> min;
  std::vector<std::vector<int>> max;
  for (int i = 0; i < n; ++i) {
    std::cin >> vi;
    v.push_back(vi);
    min.push_back(std::vector<int>(n, -1));
    max.push_back(std::vector<int>(n, -1));
  }
  
  for (int length = 0; length < n; ++length) {
    for (int i = 0; i < n - length; ++i) {
      int j = i + length;
      if (length == 0) {
        min[i][j] = v[i];
        max[i][j] = v[i];
      } else if (length == 1) {
        min[i][j] = std::min(v[i], v[j]);
        max[i][j] = std::max(v[i], v[j]);
      } else {
        min[i][j] = std::min(max[i + 1][j], max[i][j - 1]);
        max[i][j] = std::max(v[i] + min[i + 1][j], min[i][j - 1] + v[j]);
      }
    }  
  }
  return max[0][n - 1];
}

int main() {
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    int solution = solve();
    std::cout << solution << std::endl;
  }
}