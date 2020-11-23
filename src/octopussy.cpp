#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> mins(n);
  for (int i = 0; i < n; ++i) {
    cin >> mins[i];
  }
  
  for (int i = 0; i <= (n - 3) / 2; ++i) {
    mins[2 * i + 1] = min(mins[2 * i + 1], mins[i] - 1); 
    mins[2 * i + 2] = min(mins[2 * i + 2], mins[i] - 1);
  }
  
  sort(mins.begin(), mins.end());
  
  bool success = true;
  for (int i = 0; i < n; ++i) {
    if (mins[i] <= i) {
      success = false;
      break;
    }
  } 
  
  if (success) {
    cout << "yes";
  }
  else {
    cout << "no";
  }
  cout << endl;

}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}