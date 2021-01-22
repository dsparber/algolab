#include <iostream>
#include <limits>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef K::FT FT;

using namespace std;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void print(const P &p) {
    cout << setprecision(0) << fixed << floor_to_double(p.x()) << " " << floor_to_double(p.y()) << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int n; cin >> n;
  while (n > 0) {
    long x, y, a, b;
    cin >> x >> y >> a >> b;
    R ray = R(P(x, y), P(a, b));
    FT minDist;
    bool hit = false;
    P firstIntersection;
    
    vector<S> segments(n);
    for (int i = 0; i < n; ++i) {
      long r, s, t, u;
      cin >> r >> s >> t >> u;
      segments[i] = S(P(r, s), P(t, u));
    }
    
    random_shuffle(segments.begin(), segments.end());
    
    for (int i = 0; i < n; ++i) {
    
      S segment = segments[i];
      
      if (CGAL::do_intersect(ray, segment)) {
        auto intersection = CGAL::intersection(ray, segment);
        if (const P* intersectionPoint = boost::get<P>(&*intersection)) {
          FT dist = CGAL::squared_distance(xy, *intersectionPoint);
          if (!hit || dist < minDist) {
            minDist = dist;
            firstIntersection = *intersectionPoint;
          }
          hit = true;
        }
        else if (const S* intersectionSegment = boost::get<S>(&*intersection)) {
          FT dist = CGAL::squared_distance(xy, intersectionSegment->source());
          if (!hit || dist < minDist) {
            minDist = dist;
            firstIntersection = intersectionSegment->source();
          }
          hit = true;
          dist = CGAL::squared_distance(xy, intersectionSegment->target());
          if (dist < minDist) {
            minDist = dist;
            firstIntersection = intersectionSegment->target();
          }
        }
      }
    }
    
    if (!hit) {
      cout << "no" << endl;
    } else {
      print(firstIntersection);
    }
    
    cin >> n;
  }
}