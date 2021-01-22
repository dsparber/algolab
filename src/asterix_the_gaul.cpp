///4
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

struct MovesDistanceTime {
  int moves;
  long distance;
  long time;
  
  bool operator<(MovesDistanceTime& other) {
    return time < other.time;
  }
};


int n; // number of moves
int m; // amount of magic potion
long D; // distance to panoramix
long T; // number of seconds it takes for the romans to reach the druid

vector<int> d; // traversed distance for each move
vector<int> t; // time required for each move


void computeMaxDistanceRecursive(int i, int end, int numMoves, long distance, long remainingTime, vector<MovesDistanceTime> &movesDistanceTime) {
  if (remainingTime <= 0) {
    return;
  }
  
  if (i == end) {
    if (numMoves != 0) {
      movesDistanceTime.push_back(MovesDistanceTime({numMoves, distance, T - remainingTime}));
    }
    return;
  }
  
  computeMaxDistanceRecursive(i + 1, end, numMoves + 1, distance + d[i], remainingTime - t[i], movesDistanceTime);
  computeMaxDistanceRecursive(i + 1, end, numMoves, distance, remainingTime, movesDistanceTime);
}

// Compute the largest distance possible with 0 < i <= n moves
void computeMaxDistance(int start, int end, map<int, long> &maxDistance) {
  
  // Split
  int middle = (start + end) / 2;
  vector<MovesDistanceTime> movesDistanceTime1;
  vector<MovesDistanceTime> movesDistanceTime2;
  computeMaxDistanceRecursive(0, middle, 0, 0, T, movesDistanceTime1);
  computeMaxDistanceRecursive(middle, n, 0, 0, T, movesDistanceTime2);
  
  
  // Merge
  sort(movesDistanceTime1.begin(), movesDistanceTime1.end());
  sort(movesDistanceTime2.begin(), movesDistanceTime2.end());
  
  for (auto v : movesDistanceTime1) {
    maxDistance[v.moves] = max(v.distance, maxDistance[v.moves]);
  }
  for (auto v : movesDistanceTime2) {
    maxDistance[v.moves] = max(v.distance, maxDistance[v.moves]);
  }
  for (auto v1 : movesDistanceTime1) {
    for (auto v2 : movesDistanceTime2) {
      if (v1.time + v2.time < T) {
        maxDistance[v1.moves + v2.moves] = max(v1.distance + v2.distance, maxDistance[v1.moves + v2.moves]);
      }
      else {
        break;
      }
    }
  }
  
}

void solve() {

  cin >> n >> m >> D >> T;
  
  d = vector<int>(n);
  t = vector<int>(n);
  for (int i = 0; i < n; ++i) {
    cin >> d[i] >> t[i];
  }
  vector<int> s(m + 2); // additional distance covered by every move after taking i gulps
  for (int i = 1; i <= m; ++i) {
    cin >> s[i]; 
  }
  
  // Compute the largest distance possible with 0 < i <= n moves
  map<int, long> maxDistance;
  computeMaxDistance(0, n, maxDistance);

  int a = 0;
  int b = m + 1;

  while (a != b) {
    int gulps = (a + b) / 2;

    bool isFeasible = false;
    for (auto d : maxDistance) {
      int numMoves = d.first;
      long distance = d.second;
      if (distance + s[gulps] * numMoves >= D) {
        isFeasible = true;
        break;
      }
    }

    if (isFeasible) {
      b = gulps;
    }
    else {
      a = gulps + 1;
    }
  }
  
  if (a == m + 1) {
      cout << "Panoramix captured" << endl;
  }
  else {
    cout << a << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}