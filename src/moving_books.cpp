#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Strategy:
// Sort strengths and weights in ascending order
// For i = 1..n:
//  - Take all boxes that are to heavy for everyone before, but not too heavy for person i
//  - If person i carries less than the person carrying the most, take over boxes
void solve() {
  int n, m;
  cin >> n >> m;
  
  // Read strengths
  vector<int> s(n);
  for (int i = 0; i < n; ++i) {
    cin >> s[i];  
  }
  
  // Read weights
  vector<int> w(m);
  for (int i = 0; i < m; ++i) {
    cin >> w[i];  
  }
  
  // Sort strengths and weights
  sort(s.begin(), s.end());
  sort(w.begin(), w.end());
  
  // If the heaviest box is to heavy for the strongest person, it is impossible
  if (s[n - 1] < w[m - 1]) {
    cout << "impossible" << endl;
    return;
  }
  
  // Keep track what the maximum amount is someone carries
  int maxBoxes = 0;
  
  int j = 0;
  vector<int> numPeople(m + 1, 0); // How many people carry exactly j boxes
  for (int i = 0; i < n; ++i) {
    
    // Slide over boxes for counting
    int count = 0;
    while (j < m && w[j] <= s[i]) { 
      ++j;
      ++count;
    }
    numPeople[count]++;

    // A new maximum
    if (count >= maxBoxes || i == 0) {
      maxBoxes = count;
    }

    // Person i can take over boxes of other people
    else {
      // While person i has some spare capacity
      while (count < maxBoxes) {
        // Take one box form each person that is already carrying the maxBoxes
        // Make sure not to take on too many boxes
        int delta = min(numPeople[maxBoxes], maxBoxes - count);
        
        // one person now carries delta additional boxes
        numPeople[count] -= 1;
        numPeople[count + delta] += 1;
        
        // delta people now carry one box less
        numPeople[maxBoxes] -= delta;
        numPeople[maxBoxes - 1] += delta;

        // Update count for current person
        count += delta;
        
        // If there is no one left at full capacity, reduce capacity
        if (numPeople[maxBoxes] == 0) {
          maxBoxes--;
        }
      }  
    }
  }

  // Calculate time  
  int time = 3 * maxBoxes - 1;
  cout << time << endl;
  
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}