#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ij {
    int i;
    int j;
};

void solve() {
    int n; cin >> n;
    vector<int> positions;
    for (int i = 0; i < n; ++i) {
        int p; cin >> p;
        positions.push_back(p);
    }
    sort(positions.begin(), positions.end());

    int i = 0;
    int j = 0;

    int maxParasols = -1;
    int smallestDistance = 200;
    vector<int> bestPositions;

    while (i < n && j < n) {
        int width = positions[j] - positions[i];
        int parasols = j - i + 1;

        // Compute score and compare
        int distance = (width + 1) / 2;
        int bestPosition = positions[i] + distance;

        if (parasols > maxParasols || (parasols == maxParasols && distance <= smallestDistance)) {

            // New best
            if (parasols > maxParasols || distance < smallestDistance) {
                bestPositions = vector<int>();
                smallestDistance = distance;
            }
            maxParasols = parasols;
            if (width % 2 == 1) { // Odd width => best position not unique
                bestPositions.push_back(bestPosition - 1);
            }
            bestPositions.push_back(bestPosition);


        }


        // Move window
        if (positions[j + 1] - positions[i] < 201 && j < n - 1) {
            ++j;
        } else {
            ++i;
        }
    }



    cout << maxParasols << " " <<  smallestDistance << endl;
    for (int p : bestPositions) {
        cout << p << " ";
    }
    cout << endl;
}


int main() {
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
}