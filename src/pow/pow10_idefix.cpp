#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <limits>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/connected_components.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef int Info;
typedef CGAL::Triangulation_vertex_base_with_info_2<Info,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> DT;
typedef Tds::Vertex_handle Vh;
typedef std::pair<K::Point_2,Info> IPoint;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

typedef std::vector <boost::default_color_type> partition_t;
typedef typename boost::property_map <graph, boost::vertex_index_t>::type index_map_t;
typedef boost::iterator_property_map <partition_t::iterator, index_map_t> partition_map_t;

using namespace std;

void solve() {
  
  long n, m, s, k;
  cin >> n >> m >> s >> k;
  
  long x, y;
  vector<IPoint> pts(n);
  for (int i = 0; i < n; ++i)
  {
      cin >> x >> y;
      pts[i] = {K::Point_2(x, y), i};
  }

  DT dt;
  dt.insert(pts.begin(), pts.end());
  
  graph G(n);
  for (auto v = dt.finite_vertices_begin(); v != dt.finite_vertices_end(); ++v) {
      auto neighbor = v->incident_vertices();
      if (neighbor == nullptr) {
          continue;
      }
      do {
          if (!dt.is_infinite(neighbor) && CGAL::squared_distance(v->point(), neighbor->point()) <= s) {
              boost::add_edge(v->info(), neighbor->info(), G);
          }
      } while(++neighbor != v->incident_vertices());
  }
  
  // Connected components: 
  std::vector<int> component_map(n);
  int ncc =  boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 
  
  vector<int> count(ncc);
  for (int i = 0; i < m; ++i) {
    cin >> x >> y;
    auto point =  K::Point_2(x, y);
    auto nearest = dt.nearest_vertex(point);
    
    if (CGAL::squared_distance(point, nearest->point()) * 4 <= s) {
      auto component = component_map[nearest->info()];
      ++count[component];
    }
  }
  
  int a = 0;
  for (int i = 0; i < ncc; ++i) {
    a = max(a, count[i]);
  }  
  long q = 4 * s;
  cout << a << " " << q << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}