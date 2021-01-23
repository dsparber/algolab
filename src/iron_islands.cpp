#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void solve()
{
    int n; // number of islands
    int k; // number of ironborn men at your disposal
    int w; // number of waterways that start at Pyke
    cin >> n >> k >> w;

    vector<int> c(n); // number of men required to conquer island i
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    vector<int> l(w);
    vector<vector<int>> ways(w); // islands along this waterway
    for (int i = 0; i < w; ++i) {
        cin >> l[i];
        ways[i].resize(l[i]);
        for (int j = 0; j < l[i]; ++j) {
            cin >> ways[i][j];
        }
    }


    int best = 0;

    // Find solution for single waterway
    for (int i = 0; i < w; ++i) {
        int a = 0;
        int b = 0;

        int sum = c[ways[i][0]];

        while (a < l[i] && b < l[i])
        {
            if (sum == k) {
                best = max(best, b - a + 1);
            }

            // Update window
            if (sum >= k || b == l[i] - 1) {
                sum -= c[ways[i][a++]];
            }
            else {
                sum += c[ways[i][++b]];
            }
        }
    }

    // Find a solution that includes Pyke
    // Idea:
    // - compute partial sums for each waterway
    // - find two sums that together with c[0] equal k
    map<int, int> sumToDistance;
    for (int i = 0; i < w; ++i) {
        // Compute partial sums and
        vector<int> sums;
        sums.push_back(0);
        for (int j = 1; j < l[i]; ++j) {
            int sum = sums[j - 1] + c[ways[i][j]];
            if (sum + c[0] >= k) {
                break; // Sums greater k are irrelevant
            }
            sums.push_back(sum);

            // find occurrences that satisfies diff
            int diff = k - (sum + c[0]);
            auto other = sumToDistance.find(diff);
            if (other != sumToDistance.end()) {
                best = max(best, j + other->second + 1);
            }
        }
        // Add sums of this waterway to map
        for (int j = 1; j < sums.size(); ++j) {
            // If the sum is already in the map, use the larger distance
            sumToDistance[sums[j]] = max(j, sumToDistance[sums[j]]);
        }
    }

    cout << best << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}