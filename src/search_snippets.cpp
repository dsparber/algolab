#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct wordIndex {
    int index;
    int word;

    bool operator<(const wordIndex &rhs) {
        return index < rhs.index;
    }
};


void solve() {
    int n;
    cin >> n;
    vector<int> m;
    vector<vector<int>> p(n, vector<int>());
    vector<wordIndex> wordIndices;
    int in;
    int lastWordIndex = 0;
    for (int i = 0; i < n; ++i) {
        cin >> in;
        m.push_back(in);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m[i]; ++j) {
            cin >> in;
            p[i].push_back(in);
            wordIndices.push_back(wordIndex{p[i][j], i});
        }
        //sort(p[i].begin(), p[i].end());
        lastWordIndex = max(lastWordIndex, p[i][0]);
    }
    sort(wordIndices.begin(), wordIndices.end());

    int i = 0;
    int j = 0;
    vector<int> pi(n, 0);

    // Move j to first position, where all words are covered
    while (wordIndices[j].index != lastWordIndex) {
        ++j;
    }

    int w = wordIndices.size();
    int minLength = 1073741826;

    while (i < w && j < w) {

        wordIndex a = wordIndices[i];
        wordIndex b = wordIndices[j];
        int length = b.index - a.index + 1;
        minLength = min(minLength, length);

        // Check if moving i is allowed
        bool moveI = true;
        int word = a.word;
        if (pi[word] + 1 >= m[word]) {
            // Already last occurrence of word
            break;
        } else {
            int nextWordIndex = p[word][pi[word] + 1];
            moveI = a.index < nextWordIndex && nextWordIndex <= b.index;
        }


        if (moveI) {
            ++i;
            pi[word] += 1;
        } else {
            ++j;
        }


    }


    cout << minLength << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
}