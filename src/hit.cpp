#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  
  int n; cin >> n;
  while (n > 0) {
    long x, y, a, b;
    cin >> x; cin >> y; cin >> a; cin >> b;
    R ray = R(P(x, y), P(a, b));
    bool hit = false;
    for (int i = 0; i < n; ++i) {
      long r, s, t, u;
      cin >> r; cin >> s; cin >> t; cin >> u;
      
      // Already hit an obstacle, no need to test for intersection
      if (hit) {
        continue;
      }
      
      if (CGAL::do_intersect(ray, S(P(r, s), P(t, u)))) {
        hit = true;
      }
    }
    cout << (hit ? "yes" : "no") << endl; 
    
    cin >> n;
  }
}