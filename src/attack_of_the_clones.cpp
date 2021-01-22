#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

struct jedi {
  int a;
  int b;
  
  bool operator<(jedi& o) const {
    return b < o.b || (b == o.b && a < o.a);
  }
};

// Get the maximum numbers of jedis, where a < b for every jedi
int maxRegularJedis(int start, int end, vector<jedi> jedis) {
  int count = 0;
  int lastEnd = start;
  for (jedi j : jedis) {
    if (j.b >= end) {
        break;
    }
    if (j.a > lastEnd) {
        ++count;
        lastEnd = j.b; 
    }
  }
  return count;
}

void solve() {
  int n; cin >> n;
  int m; cin >> m;
  
  vector<jedi> jedis(n);
  map<int, int> jediDelta;
  int a, b;
  for (int i = 0; i < n; ++i) {
    cin >> a;
    cin >> b;
    jedis[i] = jedi({a, b});
    jediDelta[a]++;
    jediDelta[(b + 1) % m]--;
  }
  
  // Find index with smallest number of jedis
  int start = -1;
  int overlaps = 0;
  int minOverlaps = numeric_limits<int>::max();
  for (auto d : jediDelta) {
    int index = d.first;
    int delta = d.second;
    overlaps += delta;
    if (overlaps < minOverlaps) {
      minOverlaps = overlaps;
      start = index;
    }
  }
  
  vector<jedi> startJedis;
  vector<jedi> regularJedis;
  for (jedi &j : jedis) {
      // Shift start to 0
      j.a = (j.a - start + m) % m;
      j.b = (j.b - start + m) % m;

      // Overlaps start => try this jedi as first jedi
      if (j.a > j.b) {
          startJedis.push_back(j);
      }
      // No overlap
      else {
          regularJedis.push_back(j);
      }
  }
  sort(regularJedis.begin(), regularJedis.end());

  // Maximum without any of the start jedis
  int maxJedis = maxRegularJedis(-1, m, regularJedis);
  // Try every start jedi
  for (jedi j0 : startJedis) {
      int currentJedis = 1 +  maxRegularJedis(j0.b, j0.a, regularJedis);
      maxJedis = max(maxJedis, currentJedis);
  }
  cout << maxJedis << endl; 
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; 
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}