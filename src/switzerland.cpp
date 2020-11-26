#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >  graph;
typedef  boost::graph_traits<graph>::edge_descriptor      edge_desc;
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;


class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

using namespace std;

// Modeling it as a flow problem. 
// The source connects to all vertices with a positive balance, all other vertices connect to the sink.
// Since an unions total value needs to be strictly greater than zero, we know there needs to be at 
// least one province that does not need its full balance to support it. I no such province exists, 
// there can not be an union. If there is a province that does not need its full balance, the flow is 
// less than the sum of positive balances
void solve() {
  int n, m;
  cin >> n >> m;
  
  // Set up the graph
  graph G(n);
  edge_adder adder(G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  auto source = boost::add_vertex(G);
  auto target = boost::add_vertex(G);
  
  // Connect all provinces to source/target depending on balance
  int sumPositive = 0;
  int b;
  for (int i = 0; i < n; ++i) {
    cin >> b;
    if (b > 0) {
      sumPositive += b;
      adder.add_edge(source, i, b);
    }
    else {
      adder.add_edge(i, target, -b);
    }
  }
  
  // Connect provinces
  int u, v, d;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> d;
    adder.add_edge(u, v, d);
  }
  

  // Compute flow & output
  int flow = boost::push_relabel_max_flow(G, source, target);
  cout << (flow < sumPositive ? "yes" : "no") << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}