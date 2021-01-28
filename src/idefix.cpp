#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>  Vb;
typedef CGAL::Triangulation_face_base_2<K>                  Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>         Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>               Delaunay;
typedef std::pair<K::Point_2,int>                           IPoint;

using namespace std;

struct Edge {
  int u, v;
  long distance;
  
  bool operator<(const Edge& other) const {
    return distance < other.distance;
  }
};

// For a given component described by the boneDistances, compute the a value
int getA(vector<long> boneDistances, long s) {
  auto it = upper_bound(boneDistances.begin(), boneDistances.end(), s);
  return distance(boneDistances.begin(), it);
}

// For a given component described by the boneDistances and the longest edge, compute the q value
long getQ(vector<long> boneDistances, long longestEdge, int k) {
   if (boneDistances.size() >= k) {
    return max(boneDistances[k - 1], longestEdge);
  }
  return numeric_limits<long>::max();
}

// Strategy:
// - Get graph with Delaunay
// - Use Union-Find to construct connected componets
// - At each merge step compute a and q values
void solve() {
  int n, m, k;
  long s; // == 4r^2
  
  cin >> n >> m >> s >> k;

  // Constructe Delaunay triangulation of trees
  vector<IPoint> points;
  points.reserve(n);
  int x, y;
  for (int i = 0; i < n; ++i) {
    cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  
  // For each bone: find closest tree
  // Keep list for every tree t which contains the distances for all bones that have t as closest tree
  vector<vector<long>> bones(n);
  for (int i = 0; i < m; ++i) {
    cin >> x >> y;
    K::Point_2 p(x, y);
    auto vertex = t.nearest_vertex(p);
    int v = vertex->info();
    auto d = 4 * long(CGAL::squared_distance(p, vertex->point()));
    bones[v].push_back(d);
  }
  // Sort the bone lists
  for (int i = 0; i < n; ++i) {
    sort(bones[i].begin(), bones[i].end());
  }

  // Extract edges for union find
  vector<Edge> edges;
  edges.reserve(3*n);
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int u = e->first->vertex((e->second+1)%3)->info();
    int v = e->first->vertex((e->second+2)%3)->info();
    edges.push_back({u, v, long(t.segment(e).squared_length())});
  }
  std::sort(edges.begin(), edges.end());


  // Compute solution for before connecting
  int a = -1;
  long q = numeric_limits<long>::max();
  for (auto bonesOfTree : bones) {
    q = min(q, getQ(bonesOfTree, -1, k));
    a = max(a, getA(bonesOfTree, s));
  }
  

  // Connect components
  boost::disjoint_sets_with_storage<> uf(n);
  int n_components = n;
  for (auto e : edges) {
    int u = e.u;
    int v = e.v;
    int c1 = uf.find_set(u);
    int c2 = uf.find_set(v);
    if (c1 != c2) {
      
      // Link components & merge distances
      uf.link(c1, c2);
      int c = uf.find_set(c1);
      vector<long> dst;
      merge(bones[c1].begin(), bones[c1].end(), bones[c2].begin(), bones[c2].end(), back_inserter(dst));
      bones[c] = dst;
      

      // Update a & q
      q = min(q, getQ(bones[c], e.distance, k));      
      if (e.distance <= s) {
        a = max(a, getA(bones[c], s));
      }
      
      if (--n_components == 1) break;
    }
  }
  
  cout << a << " " << q << endl; 
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
