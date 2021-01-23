#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef std::result_of<K::Intersect_2(K::Ray_2,K::Segment_2)>::type IT;
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

P getIntersectionPoint(IT &intersection, P &xy) {
  if (const P* intersectionPoint = boost::get<P>(&*intersection)) {
    return *intersectionPoint;
  }

  const S* intersectionSegment = boost::get<S>(&*intersection);
  FT sourceDist = CGAL::squared_distance(xy, intersectionSegment->source());
  FT targetDist = CGAL::squared_distance(xy, intersectionSegment->target());

  if (sourceDist < targetDist) {
    return intersectionSegment->source();
  }
  return intersectionSegment->target();
}

void solve(int n) {
  long x, y, a, b;
  cin >> x >> y >> a >> b;
  P xy = P(x, y);
  R ray = R(P(x, y), P(a, b));
  FT minDist;
  bool hit = false;
  P intersection;

  vector<S> segments(n);
  for (int i = 0; i < n; ++i) {
    long r, s, t, u;
    cin >> r >> s >> t >> u;
    segments[i] = S(P(r, s), P(t, u));
  }

  random_shuffle(segments.begin(), segments.end());

  int i;
  for (i = 0; i < n; ++i) {

    S segment = segments[i];

    if (CGAL::do_intersect(ray, segment)) {
      auto rayIntersection = CGAL::intersection(ray, segment);
      intersection = getIntersectionPoint(rayIntersection, xy);
      hit = true;
      break;
    }
  }

  if (!hit) {
    cout << "no" << endl;
    return;
  }

  // Continue search
  S raySegment = S(xy, intersection);
  for (; i < n; ++i) {
    S segment = segments[i];
    if (CGAL::do_intersect(raySegment, segment)) {
      auto rayIntersection = CGAL::intersection(ray, segment);
      intersection = getIntersectionPoint(rayIntersection, xy);
      raySegment = S(xy, intersection);
    }
  }

  print(intersection);
}

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  while (n > 0) {
    solve(n);
    cin >> n;
  }
  return 0;
}