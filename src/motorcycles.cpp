#include <iostream>
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
  int i; // original index
  long y0, x1, y1; // ray description
  R ray; // trajectory of the biker
  L slope; // Slope for determining who keeps on driving

  Biker() {}
  Biker(int i, long y0, long x1, long y1) : i(i), y0(y0), x1(x1), y1(y1), ray(R(P(0, y0), P(x1, y1))) {
    if (y0 < y1) {
        slope = L(P(0, y0), P(x1, y1));
    }
    else {
        slope = L(P(0, -y0), P(x1, -y1)); // Reflect around origin to always get a positive slope
    }
  }

  // Sort by y0 value
  bool operator<(const Biker &rhs) {
      return y0 < rhs.y0;
  }
  
  // Returns true if this biker meets other and continues driving
  bool lives(const Biker &other) {
    auto result = CGAL::compare_slope(slope, other.slope);
    if (result == CGAL::Comparison_result::SMALLER || (result == CGAL::Comparison_result::EQUAL && y0 < other.y0)) { 
      return true;
    }
    return false;
  }
};


// Strategy:
// - Sort by start offset (i.e. y0)
// - Check against previous bikers only, with early termination
void solve() {
  int n; cin >> n;

  vector<Biker> b(n);
  long y0, x1, y1;
  for (int i = 0; i < n; ++i) {
    cin >> y0 >> x1 >> y1;
    b[i] = Biker(i, y0, x1, y1);
  }
  
  // Sort according to y0
  sort(b.begin(), b.end());
 
  // Compute who rides forever
  vector<bool> forever(n, true); 
  for (int i = 0; i < n; ++i) {

    // Check against previous bikers    
    for (int j = i - 1; j >= 0; --j) {

      // Ignore "dead" bikers
      if (!forever[b[j].i]) {
        continue;
      }

      // Does not intersect previous => No further tests needed
      if (!CGAL::do_intersect(b[i].ray, b[j].ray)) {
        break;
      }

      // Evaluate who keeps on driving
      if (b[i].lives(b[j])) {
        forever[b[j].i] = false;
      }
      else {
        forever[b[i].i] = false;
        break; // Driver i stops, we do not need to check against previous bikers anymore
      }
    }
  }

  // Output solution
  for (int i = 0; i < n; ++i) {
    if (forever[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  
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