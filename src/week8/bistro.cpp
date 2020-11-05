#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  DT;


using namespace std;

void solve(int n) {
  vector<K::Point_2> existing(n);
  
  long x, y;
  for (int i = 0; i < n; ++i) {
    cin >> x >> y;
    existing[i] = K::Point_2(x, y);
  }
  
  DT dt;
  dt.insert(existing.begin(), existing.end());
  
  int m;
  cin >> m;
  for (int j = 0; j < m; ++j) {
    cin >> x >> y;
    
    auto nearest = dt.nearest_vertex(K::Point_2(x, y));

    long xi = long(nearest->point().x());
    long yi = long(nearest->point().y());
    long distance = (x - xi) * (x - xi) + (y - yi) * (y - yi);
    cout << distance << endl;
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  int n;
  while (cin >> n && n > 0) {
    solve(n);
  }
  return 0;
}