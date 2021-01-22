#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;


using namespace std;

int dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
      
  int value = 0;
  for (int i = 0; i < n; ++i) {
    if (dist_map[i] != 2147483647)
    value = max(value, dist_map[i]);
  }

  return value;
}

void solve() {
  int n; cin >> n;
  int m; cin >> m;
  
  weighted_graph G(4);
  weight_map weights = boost::get(boost::edge_weight, G);

  int u, v, w;
  for (int i = 0; i < m; ++i) {
    cin >> u;
    cin >> v;
    cin >> w;
    boost::add_edge(u, v, w, G); 
  } 
  
  vector<edge_desc> mst;    // vector to store MST edges (not a property map!)

  boost::kruskal_minimum_spanning_tree(G, back_inserter(mst));

  int weight = 0;
  for (vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    weight += boost::get(boost::edge_weight_t(), G, *it);
  }

  cout << weight << " " << dijkstra_dist(G, 0) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}