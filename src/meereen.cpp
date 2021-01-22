#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>

using namespace std;

int n; // Number of fighters
int k; // Number of different types of fighters, 2 <= k <= 4
int m; // Number of fighters the audience can remember, 2 <= m <= 3

bool debug = false;

struct queue {
  vector<int> q;

  bool operator==(const queue &other) const {
    for (int i = 0; i < q.size(); ++i) {
      if (q[i] != other.q[i]) {
        return false;        
      }
    }
    return true; 
  }
  
  bool operator<(const queue &other) const {
    for (int i = 0; i < q.size(); ++i) {
      if (q[i] < other.q[i]) {
        return true;
      }
      if (q[i] > other.q[i]) {
        return false;
      }
    }
    return false; 
  }
  
  queue insert(int type) {
    vector<int> qNew(m);
    qNew[0] = type; 
    for (int i = 1; i < m; ++i) {
      qNew[i] = q[i - 1];
    }
    return {qNew};
  }
  
  int numDistinct() {
    set<int> distinct;
    for (int type : q) {
      if (type != -1) {
        distinct.insert(type);
      }
    }
    return distinct.size();
  }
};

struct state {
  queue q1, q2;
  int deltaPQ;

  bool operator<(const state &s2) const {
    queue q1Min = min(q1, q2);
    queue q1Max = max(q1, q2);
    queue q2Min = min(s2.q1, s2.q2);
    queue q2Max = max(s2.q1, s2.q2);
    return q1Min < q2Min || (q1Min == q2Min && q1Max < q2Max) || (q1Min == q2Min && q1Max == q2Max && abs(deltaPQ) < abs(s2.deltaPQ)); 
  }
  
  state insertLeft(int type) {
    return {q1.insert(type), q2, deltaPQ - 1};
  }
  state insertRight(int type) {
    return {q1, q2.insert(type), deltaPQ + 1};
  }
  
  int scoreLeft() {
    return 1000 * q1.numDistinct() - int(pow(2, abs(deltaPQ)));
  }
  int scoreRight() {
    return 1000 * q2.numDistinct() - int(pow(2, abs(deltaPQ)));
  }
};

void solve() {

  
  cin >> n >> k >> m;
  
  vector<int> q(n); // Queue of fighters
  for (int i = 0; i < n; ++i) {
    cin >> q[i];
  }
  
  
  state empty = {{vector<int>(m, -1)}, {vector<int>(m, -1)}, 0};
  
  map<state, int> states;
  
  states[empty] = 0;
  
  for (int i = 0; i < n; ++i) {
    map<state, int> newStates;
    for (auto entry : states) {
      state s0 = entry.first;
      int score = entry.second;
      
      state s1 = s0.insertLeft(q[i]);
      int s1Score = s1.scoreLeft();
      if (s1Score >= 0) {
        if (newStates.find(s1) == newStates.end() && newStates.find(s1)->second < score + s1Score) {
            newStates[s1] = score + s1Score;
        }  
      }
      
      s1 = s0.insertRight(q[i]);
      s1Score = s1.scoreRight();
      if (s1Score >= 0) {
        if (newStates.find(s1) == newStates.end() && newStates.find(s1)->second < score + s1Score) {
            newStates[s1] = score + s1Score;
        }  
      }
    }
    states = newStates;
    
    if (debug) {
      cout << "i = " << i << ", q[i] = " << q[i]  << ":" << endl;
      for (auto entry : states) {
        cout << "  left =";
        for (int v : entry.first.q1.q) {
          cout << " " << v;
        }
        cout << ", right =";
        for (int v : entry.first.q2.q) {
          cout << " " << v;
        }
        cout << ", deltaPQ = " << entry.first.deltaPQ << ", score = " << entry.second << endl;
      }
    }
  }
  
  
  // Find max value on diagonal
  int maxValue = -1;
  for (auto entry : states) {
    maxValue = max(entry.second, maxValue);
  }
  
  cout << maxValue << endl;
  
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