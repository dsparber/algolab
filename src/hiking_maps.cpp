#include <iostream>
#include <vector>
#include <limits>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangle_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Line_2 L;
typedef K::FT FT;
typedef K::Triangle_2 T;


using namespace std;

struct wordIndex {
    int index;
    int word;

    bool operator<(const wordIndex &rhs) {
        return index < rhs.index;
    }
};


P intersection(L& l1, L& l2) {
  auto i = CGAL::intersection(l1, l2);
  if (const P* p = boost::get<P>(&*i)) {
    return *p;
  }
  return P(-1, -1);
}

void solve() {
  int m, n; cin >> m; cin >> n;
  vector<P> pos;
  pos.reserve(m);
  int x, y;
  for (int i = 0; i < m; ++i) {
    cin >> x; cin >> y;
    pos.push_back(P(x, y));
  }
  
  vector<T> t;
  t.reserve(n);
  
  vector<vector<int>> p(m - 1, vector<int>());
  vector<wordIndex> wordIndices;
  int lastWordIndex = 0;
  
  int px, py, qx, qy;
  L l1, l2, l3;
  P p1, q1, p2, q2, p3, q3;
  
  for (int i = 0; i < n; ++i) {
    cin >> px; cin >> py; cin >> qx; cin >> qy;
    p1 = P(px, py); 
    q1 = P(qx, qy);
    cin >> px; cin >> py; cin >> qx; cin >> qy;
    p2 = P(px, py); 
    q2 = P(qx, qy);
    cin >> px; cin >> py; cin >> qx; cin >> qy;
    p3 = P(px, py); 
    q3 = P(qx, qy);
    
    l1 = L(p1, q1);
    l2 = L(p2, q2);
    l3 = L(p3, q3);
    
    if (l1.oriented_side(p2) < 0) {
      l1 = L(q1, p1);
    }
    if (l2.oriented_side(p1) < 0) {
      l2 = L(q2, p2);
    }
    if (l3.oriented_side(p2) < 0) {
      l3 = L(q3, p3);
    }
    
    vector<bool> pointInside(m);
    for (int j = 0; j < m; ++j) {
      auto side1 = l1.oriented_side(pos[j]);
      auto side2 = l2.oriented_side(pos[j]);
      auto side3 = l3.oriented_side(pos[j]);
      pointInside[j] = side1 >= 0 && side2 >= 0 && side3 >= 0;
    }
    
    for (int j = 0; j < m-1; ++j) {
      bool inside = pointInside[j] && pointInside[j + 1];
      if (inside) {
        p[j].push_back(i);
        wordIndices.push_back(wordIndex{i, j});
      }
    }

  }
  
  int w = wordIndices.size();
  int minLength = numeric_limits<int>::max();
  
  for (int j = 0; j < m-1; ++j) {
    lastWordIndex = max(lastWordIndex, p[j][0]);
  }
  sort(wordIndices.begin(), wordIndices.end());
  

  
  int i = 0;
  int j = 0;
  vector<int> pi(m - 1, 0);

  // Move j to first position, where all words are covered
  while (j + 1 < w && wordIndices[j + 1].index <= lastWordIndex) {
      ++j;
  }

  while (i < w && j < w) {

        wordIndex a = wordIndices[i];
        wordIndex b = wordIndices[j];
        int length = b.index - a.index + 1;
        minLength = min(minLength, length);

        // Check if moving i is allowed
        bool moveI = true;
        int word = a.word;
        if (pi[word] + 1 >= p[word].size()) {
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
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}