#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;


// To make the code more readable, we do not want to
// pass all variables to the recursive function
vector<vector<int>> children;
vector<int> parents;
vector<int> starts;
vector<int> h;
int n, m, k;

// Current path & temperatures of this path
deque<int> path;
multiset<int> pathTemperatures;


// General idea:
// Perform a "sliding window" over the tree.
// I.e. we will always keep the current path and the corresponding temperatures.
// When we discover a new child, we will append it (and its temperature) to the path.
// When the path gets to long, we will remove the first element.
// When we go back up in the recursion again, we will remove the current element (last element of path)
// and add back the parent of the first element (if it exists, i.e. if first element != tree root)
void findStarts(int u) {

    // Append newly discovered
    path.push_back(u);
    pathTemperatures.insert(h[u]);

    // If path has gotten too long, remove first element of path
    if (path.size() > m) {
        int front = path[0];
        path.pop_front();
        pathTemperatures.erase(pathTemperatures.find(h[front]));
    }

    // If the path has the desired length, we check if it is feasible
    if (path.size() == m) {
        // The first element of a multiset is the smallest, the last the largest
        int minVal = *pathTemperatures.begin();
        int maxVal = *pathTemperatures.rbegin();
        if (maxVal - minVal <= k) {
            starts.push_back(path[0]);
        }
    }

    // Explore children (recursive call)
    for (auto v : children[u]) {
        findStarts(v);
    }

    // Remove current element from path
    path.pop_back();
    pathTemperatures.erase(pathTemperatures.find(h[u]));

    // Restore first element of path
    if (path[0] != 0) {
        int parent = parents[path[0]];
        path.push_front(parent);
        pathTemperatures.insert(h[parent]);
    }
}

void solve() {
    // Read input
    cin >> n >> m >> k;

    // Read temperatures
    h = vector<int>(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    // Read tree
    children = vector<vector<int>>(n);
    parents = vector<int>(n);
    int u, v;
    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
        children[u].push_back(v);
        parents[v] = u;
    }

    // Initialize path and result container
    path = deque<int>();
    pathTemperatures = multiset<int>();
    starts = vector<int>(); // Result container

    // Compute solution
    findStarts(0);

    // Ensure elements are ordered
    sort(starts.begin(), starts.end());

    // Print solution
    int prevStart = -1;
    for (auto start : starts) {
        if (start != prevStart) { // Avoid duplicates
            prevStart = start;
            cout << start << " ";
        }
    }

    // No feasible path
    if (starts.empty()) {
        cout << "Abort mission";
    }
    cout << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}