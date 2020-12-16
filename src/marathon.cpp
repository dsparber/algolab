#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

using namespace std;

struct edge {
  int u;
  int v;
  int length;
  int width;
};

// Strategy:
// - Find all edges that are part of some shortest path
// - Run a max-flow algorithm on those edges
void solve() {
  int n, m, s, f;
  cin >> n >> m >> s >> f;

  // Dijkstra Graph
  weighted_graph G(n);

  // Read neighbors
  vector<edge> edges;
  edges.reserve(m);
  int u, v, length, width;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> width >> length;
    boost::add_edge(u, v, length, G);
    edges.push_back({u, v, length, width});
  }

  // Run dijkstra
  std::vector<int> d(n);
  boost::dijkstra_shortest_paths(G, s, boost::distance_map(boost::make_iterator_property_map( d.begin(), boost::get(boost::vertex_index, G))));

  // Flow graph
  graph gFlow(n);
  edge_adder adder(gFlow);


  // Find edges on a shortest path
  vector<edge> shortestPathEdges;
  for (auto e : edges) {
    int diff = d[e.v] - d[e.u];
    if (e.length == diff) {
      adder.add_edge(e.u, e.v, e.width);
    }
    else if (e.length == -diff) {
      adder.add_edge(e.v, e.u, e.width);
    }
  }

  // Compute flow
  long flow = boost::push_relabel_max_flow(gFlow, s, f);
  cout << flow << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while (t--)
  {
    solve();
  }
  return 0;
}