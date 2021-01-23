#include <iostream>
using namespace std;

int solve() {
  int n; cin >> n;
  int sum = 0;
  int even = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    sum += x;
    if (sum % 2 == 0) {
      ++even;
    }
  }
  int odd = n - even;
  return even * (even - 1) / 2 + odd * (odd - 1) / 2 + even;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    int solution = solve();
    cout << solution << endl;
  }
}