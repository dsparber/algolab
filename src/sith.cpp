///1
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/pending/disjoint_sets.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::pair<K::Point_2,Index> IPoint;
typedef std::tuple<int,int> Edge;
typedef std::vector<Edge> EdgeV;
typedef Tds::Vertex_handle Vh;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

using namespace std;

// Strategy:
// - Binary search for the best k
//   - For a given k, construct a Graph that contains only points p_k...p_{n-1}
//   - Find the largest connected component
void solve() {
  int n;
  long r;
  cin >> n >> r;
  long r2 = r * r;
  
  vector<IPoint> points;
  points.reserve(n);
  int x, y;
  for (int i = 0; i < n; ++i) {
    cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
 

  // Start binary search
  int a = 1;
  int b = n;
  while (a < b - 1) {

    int empireSize = (a + b) / 2;

    // Use delaunay to quickly construct graph of points outside the empire
    Delaunay dt;
    dt.insert(points.begin() + empireSize, points.end());

    graph G(n - empireSize);
    for (auto e = dt.finite_edges_begin(); e != dt.finite_edges_end(); ++e) {
      int u = e->first->vertex((e->second+1)%3)->info();
      int v = e->first->vertex((e->second+2)%3)->info();
      if (dt.segment(e).squared_length() <= r2) {
        boost::add_edge(u - empireSize, v - empireSize, G);
      }
    }

    // Compute largest connected component
    std::vector<int> component_map(n);
    int ncc = boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 

    int largestComponent = 0;
    vector<int> componentSize(ncc, 0);
    for (int i = 0; i < n - empireSize; ++i) {
      int c = component_map[i];
      componentSize[c]++;
      largestComponent = max(largestComponent, int(componentSize[c]));
    }

    // Continue binary search
    if (empireSize <= largestComponent) { 
      // Invalid solution, the empire must be at least as large as the rebel alliance (both expand equally fast)
      // => Expand empire
      a = empireSize;
    }
    else {
      b = empireSize;
    }
  }
  cout << a << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

