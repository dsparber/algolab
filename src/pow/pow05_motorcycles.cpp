#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel EPIC;
typedef EPIC::Point_2 P;
typedef EPIC::Line_2 L;
typedef EPIC::Ray_2 R;

using namespace std;

struct Biker {
  int i;
  long y0;
  long y1;
  R ray;
  L slope;
  
  bool operator<(const Biker &rhs) {
      return CGAL::compare_slope(slope, rhs.slope) == CGAL::Comparison_result::SMALLER;
  }
};


/*
Warning! This solution is not optimal
*/
void solve() {
  int n; cin >> n;
  vector<long> y0(n);
  vector<long> x1(n);
  vector<long> y1(n);
  vector<R> rays(n);
  vector<L> slopes(n);
  vector<Biker> b(n);
  for (int i = 0; i < n; ++i) {
    cin >> y0[i];
    cin >> x1[i];
    cin >> y1[i];
    rays[i] = R(P(0, y0[i]), P(x1[i], y1[i]));
    if (y0[i] < y1[i]) {
        slopes[i] = L(P(0, y0[i]), P(x1[i], y1[i]));
    }
    else {
        slopes[i] = L(P(0, -y0[i]), P(x1[i], -y1[i]));
    }
    b[i] = Biker({i, y0[i], y1[i], rays[i], slopes[i]});
  }
  
  sort(b.begin(), b.end());
 
  vector<bool> forever(n, true); 
  for (int i = 0; i < n; ++i) {
    
    // Horizontal is always first
    if (b[i].y0 == b[i].y1) {
      continue;
    }
    
    // Dead can not ride forever
    if (!forever[b[i].i]) {
      continue;
    }
    
    for (int j = i + 1; j < n; ++j) {
      
      if (!forever[b[j].i]) {
        continue;
      }
      
      if (CGAL::do_intersect(b[i].ray, b[j].ray)) {
        auto result = CGAL::compare_slope(b[i].slope, b[j].slope);
        //cout << i << " vs. " << j << ": " << result << endl;
        if (result == CGAL::Comparison_result::SMALLER || (result == CGAL::Comparison_result::EQUAL && b[i].y0 < b[j].y0)) { // i wins
          forever[b[j].i] = false;
        }
        else {
          forever[b[i].i] = false;
        }
      }
    }
    
    
  }
  for (int i = 0; i < n; ++i) {
    if (forever[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}