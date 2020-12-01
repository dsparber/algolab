#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, k, w;
    cin >> n >> k >> w;

    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    int l, r;
    vector<vector<int>> ways(w);
    for (int i = 0; i < w; ++i) {
        cin >> l;
        ways[i].reserve(l);
        for (int j = 0; j < l; ++j) {
            cin >> r;
            ways[i].push_back(r);
        }
    }

    int best = 0;

    if (w == 1) {
        int i = 0;
        int j = 0;
        int s = ways[0].size();

        int sum = c[ways[0][0]];

        while (i < s && j < s) {
            if (sum == k) {
                best = max(best, j - i + 1);
            }
            if (sum >= k || j == s - 1) {
                sum -= c[ways[0][i++]];
            }
            else {
                sum += c[ways[0][++j]];
            }
        }
    }

    for (int w1 = 0; w1 < w; ++w1) {
        for (int w2 = w1 + 1; w2 < w; ++w2) {
            int s1 = ways[w1].size();
            int s2 = ways[w2].size();
            int s = s1 + s2 - 1;
            vector<int> path(s);
            for (int i = s1 - 1; i >= 0; --i) {
                path[s1 - i - 1] = ways[w1][i];
            }
            for (int i = 1; i < s2; ++i) {
                path[s1 + i - 1] = ways[w2][i];
            }

            int i = 0;
            int j = 0;

            int sum = c[path[0]];

            while (i < s && j < s) {
                if (sum == k) {
                    best = max(best, j - i + 1);
                }
                if (sum >= k || j == s - 1) {
                    sum -= c[path[i++]];
                }
                else {
                    sum += c[path[++j]];
                }
            }
        }
    }

    cout << best << endl;
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}