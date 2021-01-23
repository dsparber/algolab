///4
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

struct DistanceTime {
  long distance;
  long time;
  
  bool operator<(const DistanceTime& other) const {
    return time < other.time;
  }
};


int n; // number of moves
int m; // amount of magic potion
long D; // distance to panoramix
long T; // number of seconds it takes for the romans to reach the druid

vector<long> d; // traversed distance for each move
vector<long> t; // time required for each move
vector<long> s; // additional distance covered by every move after taking i gulps


void computeDistanceTimePairs(int i, int end, int gulps, long distance, long remainingTime, vector<DistanceTime> &distanceTime) {
  if (remainingTime <= 0) {
    return;
  }
  
  if (i == end) {
    if (distance > 0) {
      distanceTime.push_back({distance, T - remainingTime});
    }
    return;
  }

  // Use move
  computeDistanceTimePairs(i + 1, end, gulps, distance + d[i] + s[gulps], remainingTime - t[i], distanceTime);

  // Do not use move
  computeDistanceTimePairs(i + 1, end, gulps, distance, remainingTime, distanceTime);
}

bool isFeasible(int gulps) {
  
  // Split
  vector<DistanceTime> distanceTime1;
  vector<DistanceTime> distanceTime2;
  computeDistanceTimePairs(0, n / 2, gulps, 0, T, distanceTime1);
  computeDistanceTimePairs(n / 2, n, gulps, 0, T, distanceTime2);
  
  
  // Sort by time
  sort(distanceTime1.begin(), distanceTime1.end());
  sort(distanceTime2.begin(), distanceTime2.end());

  // Replace distance with max-distance for a given time
  for (int i = 1; i < distanceTime1.size(); ++i) {
    distanceTime1[i].distance = max(distanceTime1[i - 1].distance, distanceTime1[i].distance);
  }
  for (int i = 1; i < distanceTime2.size(); ++i) {
    distanceTime2[i].distance = max(distanceTime2[i - 1].distance, distanceTime2[i].distance);
  }

  // The maximal element of a single list is sufficient
  if (distanceTime1.back().distance >= D || distanceTime2.back().distance >= D) {
    return true;
  }

  // Merge both lists
  for (auto e1 : distanceTime1) {

    // Binary search in second list
    int a = 0;
    int b = distanceTime2.size() - 1;

    while (a != b) {
      int middle = (a + b + 1) / 2;

      auto e2 = distanceTime2[middle];

      if (e1.time + e2.time < T) {
        a = middle;
      } else {
        b = middle - 1;
      }
    }
    auto e2 = distanceTime2[a];

    // The combination is feasible
    if (e1.time + e2.time < T && e1.distance + e2.distance >= D) {
      return true;
    }
  }
  return false;
}

void solve() {

  cin >> n >> m >> D >> T;
  
  d = vector<long>(n);
  t = vector<long>(n);
  for (int i = 0; i < n; ++i) {
    cin >> d[i] >> t[i];
  }
  s = vector<long>(m + 2);
  for (int i = 1; i <= m; ++i) {
    cin >> s[i]; 
  }

  // Binary search over number of gulps
  int a = 0;
  int b = m + 1;

  while (a != b) {
    int gulps = (a + b) / 2;

    if (isFeasible(gulps)) {
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