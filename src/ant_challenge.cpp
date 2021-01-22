// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

void solve()
{
  int n; cin >> n;
  int m; cin >> m;
  int s; cin >> s;
  int a; cin >> a;
  int b; cin >> b;

  
  vector<weighted_graph> graphs(s, weighted_graph(n));
  vector<weight_map> weights(s);
  for (int i = 0; i < s; ++i) {
    weights[i] = boost::get(boost::edge_weight, graphs[i]);
  }
  
  int u, v, w;
  for (int i = 0; i < m; ++i) {
    cin >> u;
    cin >> v;
    for (int j = 0; j < s; ++j) {
      cin >> w;
      boost::add_edge(u, v, w, graphs[j]);
    }
  }

  int h;
  for (int i = 0; i < s; ++i) {
    cin >> h;
  }

  weighted_graph G(n);

  for (int i = 0; i < s; ++i) {
    vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(graphs[i], back_inserter(mst));
    for (auto e : mst) {
      int u = boost::source(e, graphs[i]);
      int v = boost::target(e, graphs[i]);
      boost::add_edge(u, v, weights[i][e], G);
    }
  }
  
  cout << dijkstra_dist(G, a, b) << endl;

}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}