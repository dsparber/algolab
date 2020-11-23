#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <limits>

#include <boost/graph/topological_sort.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/connected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int>> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::vertex_descriptor edge_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;

using namespace std;

struct edge {
  int vertex;
  int debt;
};

void solve() {
  int n, m;
  cin >> n >> m;
  
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  
  graph G(n);

  int u, v, d;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> d;
    boost::add_edge(u, v, d, G);
  }
  
  
  std::vector<int> component_map(n);
  int ncc = boost::strong_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 
  
  
  vector<int> componentValue(ncc, 0);
  for (int i = 0; i < n; ++i) {
    int component = component_map[i];
    componentValue[component] += b[i];
  }

  graph C(ncc);
  edge_it e, end;
  map<tuple<int, int>, int> edges;
  for (boost::tie(e, end) = boost::edges(G); e != end; ++e) {
    u = component_map[boost::source(*e, G)];
    v = component_map[boost::target(*e, G)];
    if (u != v) {
      edges[{u, v}] += boost::get(boost::edge_weight, C)[*e];
    }
  }
  for (auto edge : edges) {
    tuple<int, int> uv;
    tie(uv, d) = edge; 
    tie(u, v) = uv;
    boost::add_edge(u, v, d, C);
  }
  
  vector<int> topo;
  boost::topological_sort(C, std::back_inserter(topo));
  
  bool debug = false;
  
  for (int u : topo) {
    if (debug) cout << "out-edges of " << u << ": ";
    out_edge_it e, end;
    int value = componentValue[u];
    for (boost::tie(e, end) = boost::out_edges(u, C); e != end; ++e) {
      int v = boost::target(*e, C);
      int debt = boost::get(boost::edge_weight, C)[*e];
      value += max(-debt, componentValue[v]);
      if (debug) cout << v << ", d = " << debt << "\t";
    }
    if (debug) cout << endl;
    if (debug) cout << "Value of " << u << ": " << value << endl;
    if (value > 0) {
      cout << "yes" << endl;
      return;
    }
    
  }
  
  
  cout << "no" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}