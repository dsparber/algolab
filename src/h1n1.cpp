#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <queue>
#include <limits>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K>   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int, K>  Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef K::FT FT;

using namespace std;

struct Neighbor {
  int vertex;
  FT width;
};

void solve(int numPoints) {

  long x, y;
  vector<K::Point_2> pts(numPoints);
  for (int i = 0; i < numPoints; ++i) {
    cin >> x >> y;
    pts[i] = {x, y};
  }
  Delaunay dt;
  dt.insert(pts.begin(), pts.end());
  
  int id = 1;
  for (auto f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
    f->info() = id++;
  }

  int n = id;
  vector<vector<Neighbor>> neighbors(n);
  for (auto f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
    int u = f->info();
    
    for (int i = 0; i < 3; ++i) {
      auto f2 = f->neighbor(i);
      int v = dt.is_infinite(f2) ? 0 : f2->info();
      auto p1 = f->vertex((i + 1) % 3)->point();
      auto p2 = f->vertex((i + 2) % 3)->point();
      FT width = CGAL::squared_distance(p1, p2);
      
      neighbors[u].push_back({v, width});
      if (v == 0) {
        neighbors[v].push_back({u, width});
      }
    }
  }
  
  FT maxValue = FT(numeric_limits<long>::max());
  
  vector<FT> width(n, -1);
  priority_queue<tuple<FT, int>> queue; 
  queue.push({maxValue, 0});
  
  while (!queue.empty()) {

    FT w = get<0>(queue.top());
    int u = get<1>(queue.top());
    queue.pop();

    if (width[u] != -1) {
      continue;
    }
    
    width[u] = w;

    for (Neighbor n : neighbors[u]) {
      FT wn = CGAL::min(n.width, w);
      queue.push({wn, n.vertex});
    }
  }

  int m;
  cin >> m;
  long d;
  for (int i = 0; i < m; ++i) {
    cin >> x >> y >> d;
    
    K::Point_2 p(x, y);
    
    if (CGAL::squared_distance(p, dt.nearest_vertex(p)->point()) < FT(d)) {
      cout << "n";
      continue;
    }
    
    auto f = dt.locate(p);
    int v = dt.is_infinite(f) ? 0 : f->info();

    if (width[v] >= FT(4) * FT(d)) {
      cout << "y";
    }
    else {
      cout << "n";
    }
    
  }
  cout << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  int n; 
  cin >> n;
  while (n != 0) {
    solve(n);
    cin >> n;
  }
  return 0;
}
