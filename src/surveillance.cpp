#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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

void solve() {
  int n; cin >> n;
  int m; cin >> m;
  int k; cin >> k;
  int l; cin >> l;
  
  graph G(2 * n);
  edge_adder adder(G);
  
  vertex_desc source = boost::add_vertex(G);
  vertex_desc target = boost::add_vertex(G);
  
  int x;
  for (int i = 0; i < k; ++i) {
    cin >> x;
    adder.add_edge(source, x, 1);
    adder.add_edge(n + x, target, 1);
  }
  
  for (int i = 0; i < l; ++i) {
    cin >> x;
    adder.add_edge(x, n + x, 1);
  }

  
  int u, v;
  for (int i = 0; i < m; ++i) {
    cin >> u;
    cin >> v;
    adder.add_edge(u, v, k);
    adder.add_edge(n + u, n + v, 1); 
  }
  
  long flow = boost::push_relabel_max_flow(G, source, target);
  cout << flow << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}