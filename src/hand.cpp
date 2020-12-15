#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/pending/disjoint_sets.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef int                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  DT;
typedef std::pair<K::Point_2,Index> IPoint;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, long> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

struct Edge {
  int u, v;
  long w;
  
  bool operator<(Edge e) {
    return w < e.w;
  }
};

typedef std::vector<Edge> EdgeV;

using namespace std;

int maxFamilies(vector<int> &componentsOfSize, int k) {
  int f = componentsOfSize[k];
  if (k == 4) {
    if (componentsOfSize[3] <= componentsOfSize[1]) {
      f += componentsOfSize[3];
      f += ((componentsOfSize[1] - componentsOfSize[3]) / 2 + componentsOfSize[2]) / 2;
    }
    else {
      f += componentsOfSize[1];
      f += ((componentsOfSize[3] - componentsOfSize[1]) + componentsOfSize[2]) / 2;
    }
  }
  else if (k == 3) {
    if (componentsOfSize[2] <= componentsOfSize[1]) {
      f += componentsOfSize[2];
      f += (componentsOfSize[1] - componentsOfSize[2]) / 3;
    }
    else {
      f += componentsOfSize[1];
      f += (componentsOfSize[2] - componentsOfSize[1]) / 2;
    }
  }
  else if (k == 2) {
    f += componentsOfSize[1] / 2;
  }
  return f;
}


void solve() {
  int n, k, f0;
  long s0;
  cin >> n >> k >> f0 >> s0;
  
  vector<IPoint> pts(n);
  for (std::size_t i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    pts[i] = {{x, y}, i};
  }
  
  DT dt;
  dt.insert(pts.begin(), pts.end());
  
  EdgeV edges;
  edges.reserve(3*n);
  for (auto e = dt.finite_edges_begin(); e != dt.finite_edges_end(); ++e) {
    int u = e->first->vertex((e->second+1)%3)->info();
    int v = e->first->vertex((e->second+2)%3)->info();
    if (u > v) swap(u, v);
    edges.push_back({u, v, long(dt.segment(e).squared_length())});
  }
  
  std::sort(edges.begin(), edges.end());
  
  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  vector<int> sizeOfComponent(n, 1);
  vector<int> componentsOfSize(k + 1, 0);
  int s = -1;
  int f = -1;
  componentsOfSize[1] = n;
  vector<long> squaredDistances;
  for (auto e : edges) {
    Index c1 = uf.find_set(e.u);
    Index c2 = uf.find_set(e.v);
    if (c1 != c2) {
      
      int fMax = maxFamilies(componentsOfSize, k);
      
      if (fMax >= f0) {
        s = e.w;
      }
      if (e.w >= s0) {
        f = max(f, fMax);
      }
      
      squaredDistances.push_back(e.w);
      
      uf.link(c1, c2);
      int c = uf.find_set(c1);
      
      componentsOfSize[sizeOfComponent[c1]] -= 1;
      componentsOfSize[sizeOfComponent[c2]] -= 1;
      sizeOfComponent[c] = min(k, sizeOfComponent[c1] + sizeOfComponent[c2]);
      componentsOfSize[sizeOfComponent[c]] += 1;
      
      if (--n_components == 1) break;
    }
  }
  int fMax = maxFamilies(componentsOfSize, k);
  f = max(f, fMax);
  
  cout << squaredDistances[n - f0] << " " << f << endl;
  // squaredDistances[n - f0]
}


int main()
{
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
