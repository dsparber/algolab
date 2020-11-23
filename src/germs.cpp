#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K_sqrt;
typedef CGAL::Delaunay_triangulation_2<K>  DT;


using namespace std;

void solve(int n) {

  int l, b, r, t;
  cin >> l >> b >> r >> t;
  
  long x, y;
  vector<K::Point_2> pts(n);
  for (int i = 0; i < n; ++i) {
    cin >> x >> y;
    pts[i] = K::Point_2(x, y);
  }
  
  DT dt;
  dt.insert(pts.begin(), pts.end());
  
  vector<double> times;
  times.reserve(n);
  for (auto v = dt.vertices_begin(); v != dt.vertices_end(); ++v) {
    long xi = long(v->point().x());
    long yi = long(v->point().y());

    auto nearest = CGAL::nearest_neighbor(dt, v->handle());

    double maxRadius = numeric_limits<double>::max();

    if (nearest != nullptr) {
      long xj = long(nearest->point().x());
      long yj = long(nearest->point().y());

      // Squared distance to neighbor
      long squaredDistance = (xi - xj) * (xi - xj) + (yi - yj) * (yi - yj);
      maxRadius = sqrt(squaredDistance) / 2;

    }
    // Distance to boarder
    long closestBorder = abs(xi - l);
    closestBorder = min(closestBorder, abs(xi - r));
    closestBorder = min(closestBorder, abs(yi - t));
    closestBorder = min(closestBorder, abs(yi - b));

    maxRadius = min(maxRadius, (double) closestBorder);

    // r = t^2 + 0.5
    // t^2 = r - 0.5
    // t = sqrt(r - 0.5)
    auto time = 0.;
    if (maxRadius - 0.5 > 0){
      time = sqrt(maxRadius - 0.5);
    }
    times.push_back(time);
  }

  sort(times.begin(), times.end());

  cout << ceil(times[0]) << " " << ceil(times[n / 2]) << " " << ceil(times[n - 1]) << endl;

}


int main() {
  ios_base::sync_with_stdio(false);
  int n;
  while (cin >> n && n > 0) {
    solve(n);
  }
  return 0;
}