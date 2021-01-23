#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int solve() {
  int n; cin >> n;
  int max_index; cin >> max_index;
  for (int i = 1; i < n; ++i) {
    if (max_index <= i) {
      // Consume rest of input
      for (int j = i; j < n; ++j) {
        cin >> max_index;
      }
      return i;
    }
    int h; cin >> h;
    max_index = max(max_index, h + i);
  }
  return n;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    int solution = solve();
    cout << solution << endl;
  }
}