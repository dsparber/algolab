#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>

using namespace std;

int mask;
int differenceOffset = 12;

struct Queue
{
  int a, b, c;

  // Count the number of distinct elements in the queue
  int numDistinct() {
    set<int> abc = {0, a, b, c};
    return abc.size() - 1;
  }

  // Insert a new value and return a new queue
  Queue insert(int value) {
    return {value, a, b};
  }

  // Encode as int
  int encode() const {
    return a + (b << 3) + (c << 6);
  }
};

// Decode a queue from an integer value
Queue decodeQueue(int value) {
  int a = value & 7;
  int b = (value >> 3) & 7;
  int c = 0; // We do not save the last element
  return {a, b, c};
}


struct State {
  Queue north;
  Queue south;
  int difference;

  // Encode as int
  int encode() const {
    return ((difference + differenceOffset) << 18) + ((south.encode() & mask) << 9) + (north.encode() & mask);
  }

  // Compute the score for a given queue
  int computeScore(bool useNorth) {
    int numDistinct = useNorth ? north.numDistinct() : south.numDistinct();
    return numDistinct * 1000 - int(pow(2, abs(difference)));
  }
};

// Decode a state from an integer value
State decodeState(int value) {
  int north = value & mask;
  int south = (value >> 9) & mask;
  int difference = (value >> 18) - differenceOffset;
  return {decodeQueue(north), decodeQueue(south), difference};
}

// Insert a state into the states map if the score is positive
void insertOrUpdate(State state, int score, int prevScore, map<int, int> &states) {
  if (score < 0) {
    return;
  }
  int encoded = state.encode();
  states[encoded] = max(prevScore + score, states[encoded]);
}

void solve() {

  int n; // Number of fighters
  int k; // Number of different types of fighters, 2 <= k <= 4
  int m; // Number of fighters the audience can remember, 2 <= m <= 3
  cin >> n >> k >> m;
  
  vector<int> fighters(n); // Queue of fighters
  for (int i = 0; i < n; ++i) {
    cin >> fighters[i];
    fighters[i]++; // Offset type by one to reserve 0 for empty
  }
  
  int b = 3 * (m - 1); // Number of bits needed to encode a queue
  mask = (1 << b) - 1; // In binary: '1' repeated b times

  
  State initalState = {{0, 0, 0}, {0, 0, 0}, 0};
  
  map<int, int> currentStates;
  currentStates[initalState.encode()] = 0;
  
  for (int fighter : fighters) {
    map<int, int> nextStates;
    for (auto entry : currentStates) {
      int score = entry.second;
      auto state = decodeState(entry.first);

      State nextNorth = {state.north.insert(fighter), state.south, state.difference - 1};
      State nextSouth = {state.north, state.south.insert(fighter), state.difference + 1};

      int scoreNorth = nextNorth.computeScore(true);
      int scoreSouth = nextSouth.computeScore(false);

      insertOrUpdate(nextNorth, scoreNorth, score, nextStates);
      insertOrUpdate(nextSouth, scoreSouth, score, nextStates);
    }
    currentStates = nextStates;
  }
  
  
  // Find max value
  int maxValue = -1;
  for (auto entry : currentStates) {
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