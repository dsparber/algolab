#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;


struct boat {
  int length;
  int ringPosition;
  
  bool operator<(boat &o) const {
    return ringPosition < o.ringPosition;
  }
};

void solve() {
  int n; cin >> n;
  vector<boat> boats(n);
  int boatLength, ringPosition;
  for (int i = 0; i < n; ++i) {
    cin >> boatLength;
    cin >> ringPosition;
    boats[i] = boat({boatLength, ringPosition});
  }
  sort(boats.begin(), boats.end());
  
  int end = numeric_limits<int>::min();
  int count = 0;
  int lastIndex = -1;
  
  while (true) {

    // Initialization
    int i = lastIndex + 1;
    int firstEnd = numeric_limits<int>::max();
    int firstEndIdx = -1;
    
    while (i < n) {
      ringPosition = boats[i].ringPosition; 
      boatLength = boats[i].length;
      int boatStart = max(end, ringPosition - boatLength); 
      if (boatStart > ringPosition) { // Not a valid placement
          ++i; 
          continue;
      }
      if (boatStart > firstEnd) { // Can not be optimal
          break;
      }
      int currentEnd = boatStart + boatLength;
      if (currentEnd < firstEnd) { // New optimum
        firstEnd = currentEnd;
        firstEndIdx = i;
      }
      ++i;
    }
    
    // No more boats possible
    if (firstEndIdx == -1) {
      break;
    }
    
    // Take boat and find next boat
    lastIndex = firstEndIdx;
    end = firstEnd;
    ++count;
  }
  cout << count << endl;
  
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}