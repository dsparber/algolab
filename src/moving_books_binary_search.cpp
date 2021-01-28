#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> s;
vector<int> w;

bool isFeasible(int k) {
  
  long n = s.size();
  long m = w.size();
  
  if (n * k < m) {
    return false;
  }
  
  int j = m - 1;
  for (int i = n - 1; i >= 0 && j >= 0; --i) {
    if (s[i] < w[j]) {
      return false;
    }
    j -= k;
  }
  
  return true;
}

void solve() {
  int n, m;
  cin >> n >> m;
  
  s = vector<int>(n);
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }
  
  w = vector<int>(m);
  for (int i = 0; i < m; ++i) {
    cin >> w[i];
  }

  sort(s.begin(), s.end());
  sort(w.begin(), w.end());
  
  if (w.back() > s.back()) {
    cout << "impossible" << endl;
    return;
  }
  
  int a = 1;
  int b = w.size();
  
  while (a != b) {
    int m = (a + b) / 2;
    if (isFeasible(m)) {
      b = m;
    }
    else {
      a = m + 1;
    }
  }
  
  cout << (3 * a - 1) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}