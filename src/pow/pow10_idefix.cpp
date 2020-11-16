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
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT FT;
typedef long Info;
typedef CGAL::Triangulation_vertex_base_with_info_2<Info,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> DT;
typedef Tds::Vertex_handle Vh;
typedef std::pair<K::Point_2,Info> IPoint;
typedef std::tuple<Info,Info,long> Edge;
typedef std::vector<Edge> EdgeV;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

typedef std::vector <boost::default_color_type> partition_t;
typedef typename boost::property_map <graph, boost::vertex_index_t>::type index_map_t;
typedef boost::iterator_property_map <partition_t::iterator, index_map_t> partition_map_t;

using namespace std;


void solve() {
  
  // Input parameters
  unsigned long n, m, s, k;
  cin >> n >> m >> s >> k;
  
  // Delaunay triangulation for quicker proximity queries
  long x, y;
  vector<IPoint> pts(n);
  for (int i = 0; i < n; ++i)
  {
      cin >> x >> y;
      pts[i] = {K::Point_2(x, y), i};
  }
  DT dt;
  dt.insert(pts.begin(), pts.end());
  
  
  // Compute connected components for part (a)
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
  vector<int> component_map(n);
  int ncc =  boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 
  
  // Count for part (a)
  vector<int> count(ncc);
  
  // For each tree i, keep list of bones which have tree i as closest tree
  vector<vector<long>> distances(n, vector<long>());
  for (int i = 0; i < m; ++i) {
    cin >> x >> y;
    auto point =  K::Point_2(x, y);
    auto nearest = dt.nearest_vertex(point);
    
    long xn = long(nearest->point().x());
    long yn = long(nearest->point().y());

    // Distance metric
    long squaredDistanceTimes4 = 4 * ((x - xn) * (x - xn) + (y - yn) * (y - yn));
    
    if (squaredDistanceTimes4 <= s) {
      auto component = component_map[nearest->info()];
      ++count[component];
    }
    
    distances[nearest->info()].push_back(squaredDistanceTimes4);
  }
  
  // For part (a) simply output connected component with highest number of bones
  int a = 0;
  for (int i = 0; i < ncc; ++i) {
    a = max(a, count[i]);
  }
  
  
  // Start of main logic for part (b). 
  // Sort distances. Later needed for efficiency
  for (int i = 0; i < n; ++i) {
    sort(distances[i].begin(), distances[i].end());
  }

  // Save the currently best value for q
  long q = numeric_limits<long>::max();
  
  // Find best values without connections between trees
  for (int i = 0; i < n; ++i) {
    // If this tree already has k bones
    if (distances[i].size() >= k) {
      // Extract distance to k-closest bone
      q = min(q, distances[i][k - 1]);
    }
  }


  // Extract edges and sort by length
  // Later, we will use union-find and merge components based on these edges
  EdgeV edges;
  edges.reserve(3*n);
  for (auto e = dt.finite_edges_begin(); e != dt.finite_edges_end(); ++e) {
    Info i1 = e->first->vertex((e->second+1)%3)->info();
    Info i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, long(dt.segment(e).squared_length()));
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool { return std::get<2>(e1) < std::get<2>(e2);});
      

  // Setup and initialize union-find data structure
  boost::disjoint_sets_with_storage<> uf(n);
  Info n_components = n;
  
  // Process edges in order of increasing length
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    
    // Determine components of endpoints
    Info c1 = uf.find_set(std::get<0>(*e));
    Info c2 = uf.find_set(std::get<1>(*e));
    
    if (c1 != c2) {
      // this edge connects two different components
      uf.link(c1, c2);
      auto cUnion = uf.find_set(c2);
      
      // Extract distance from edge
      auto distance = std::get<2>(*e);
      
      // Get distances for components c1 and c2
      auto& v1 = distances[c1];
      auto& v2 = distances[c2];
      
      // Merge distances and save to new component cUnion
      vector<long> dst;
      dst.reserve(v1.size() + v2.size());
      std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));
      distances[cUnion] = dst;
      
      // If enough bones, update according to k-closest
      if (dst.size() >= k) {
        q = min(q, max(distance, dst[k - 1]));
      }

      // Break when done
      if (--n_components == 1) break;
    }
  }  
  
  // Special case: entire forest needed
  if (q == numeric_limits<long>::max()) {
    q = distances[uf.find_set(0)][k - 1];
  }
  
  // Finally, output the solution :D
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