// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

int index(int v, int k, int n) {
  return k * n + v;
}

void solve()
{
  int n; std::cin >> n;
  int m; std::cin >> m;
  int k; std::cin >> k;
  int x; std::cin >> x;
  int y; std::cin >> y;


  weighted_graph G;

  int a, b, c, d;
  for (int i = 0; i < m; ++i) {
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> d;

    for (int j = 1; j <= k; ++j) {
      boost::add_edge(a + j * n, b + (j - d) * n, c, G); 
      boost::add_edge(b + j * n, a + (j - d) * n, c, G); 
    }
    boost::add_edge(a, b, c, G); 
    boost::add_edge(b, a, c, G);  
  }

  std::cout << dijkstra_dist(G, x + k * n, y) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}