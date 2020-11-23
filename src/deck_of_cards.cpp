#include <iostream>
#include <vector>

using namespace std;

void solve() {
  int n; cin >> n;
  int k; cin >> k;
  int vi;
  vector<int> v;
  for (int i = 0; i < n; ++i) {
    cin >> vi;
    v.push_back(vi);
  }
  int i = 0, j = 0;
  int bestI = 0, bestJ = 0;
  int best = 1073741834; 
  int currentSum = 0; 
  int value; 
  while (j < n) {
    
    currentSum += v[j];
    value = abs(k - currentSum);

    while (i <= j) {
      if (abs(k - (currentSum - v[i])) < value) {
        currentSum -= v[i];
        ++i;
        value = abs(k - currentSum);
      }
      else {
        break;
      }
    }
    
    if (value < best) {
      best = value;
      bestI = i; 
      bestJ = j;
    }
    ++j;
  }
  cout << bestI << " " << bestJ << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}