#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; 

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    //std::cout << from << " -> " << to << ": capacity = " << capacity << ", cost = " << cost << std::endl;
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

using namespace std;

struct elephant {
  int x, y, cost, capacity;
};

// Compute max flow min cost given a limit for the flow
tuple<int, int> flowAndCost(int n, int start, int end, vector<elephant> &elephants, int flowLimit, int budget) {
  graph G(n);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  for (auto e : elephants) {
    adder.add_edge(e.x, e.y, e.capacity, e.cost);
  }
  
  int source = boost::add_vertex(G);
  int target = boost::add_vertex(G);
  adder.add_edge(source, start, flowLimit, 0);
  adder.add_edge(end, target, flowLimit, 0);

  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  int flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e) {
      flow += c_map[*e] - rc_map[*e];     
  }
  int cost = boost::find_flow_cost(G);
  return {flow, cost};
}

// Check if it is feasible to transport numSuitcases suitcases
bool isFeasible(int n, int start, int end, vector<elephant> &elephants, int numSuitcases, int budget) {
  int flow, cost;
  tie(flow, cost) = flowAndCost(n, start, end, elephants, numSuitcases, budget);
  
  if (flow < numSuitcases) {
    return false;
  }
  return cost <= budget;
}

// Strategy:
// - Binary search to find largest feasible number
void solve() {
  int n, m, budget, start, end;
  cin >> n >> m >> budget >> start >> end;
  
  int x, y, cost, capacity;
  vector<elephant> elephants;
  elephants.reserve(m);
  for (int i = 0; i < m; ++i) {
    cin >> x >> y >> cost >> capacity;
    elephants.push_back({x, y, cost, capacity});
  }
  
  // Find an upper bound (what is the max flow?)
  int maxFlow = get<0>(flowAndCost(n, start, end, elephants, numeric_limits<int>::max(), budget));
  
  // Binary search for highest feasible number of elephants
  int a = 0;
  int b = maxFlow;
  while (a != b) {
    int m = a + (b - a + 1) / 2;
    
    if (isFeasible(n, start, end, elephants, m, budget)) {
      a = m;
    }
    else {
      b = m - 1;
    }
  }
  
  cout << a << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
      solve();
    }
    return 0;
}
