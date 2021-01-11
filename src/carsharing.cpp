#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long>>>>> graph;

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it;


class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
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

// Strategy:
// - Build a space-time graph, i.e. a vertex is described by a tuple (i, t) where i is the rental station and t is the time
//   - We add edges for every booking and for parking (stay at the same station until the next time step)
//   - Use Maxflow-Mincost to solve the problem
void solve() {
  
  // Read input
  int n, m;
  cin >> n >> m;
  
  vector<int> l(m); // initially available cars
  int sumCars = 0; // How many cars are there in total?
  for (int j = 0; j < m; ++j) {
    cin >> l[j];
    sumCars += l[j];
  }
  
  // Save the relevant timesteps for each station (a timestep is only relevant if a booking starts or ends at the given station)
  vector<set<int>> timePoints(m); 
  
  vector<int> s(n); // source
  vector<int> t(n); // target
  vector<int> d(n); // departure time
  vector<int> a(n); // arrival time
  vector<int> p(n); // profit
  int tMax = 0;
  for (int i = 0; i < n; ++i) {
    
    // Read input
    cin >> s[i] >> t[i] >> d[i] >> a[i] >> p[i];
    --s[i]; --t[i]; // convert 1-based to 0-based indices
    
    // Save relevant time points
    timePoints[s[i]].insert(d[i]);
    timePoints[t[i]].insert(a[i]);
    tMax = max(tMax, a[i]);
  }
  
  // Time 0 and tMax are relevant for connecting to source and target
  for (int j = 0; j < m; ++j) {
    timePoints[j].insert(0);
    timePoints[j].insert(tMax);
  }
  
  // For every station:
  // - Assign a vertex id to every time point 
  // - Sort relevant time points
  vector<map<int, int>> timeToVertex(m);
  vector<vector<int>> sortedTimePoints(m);
  int id = 0;
  for (int j = 0; j < m; ++j) {
    for (int t : timePoints[j]) {
      timeToVertex[j][t] = id++;
      sortedTimePoints[j].push_back(t);
    }
    sort(sortedTimePoints[j].begin(), sortedTimePoints[j].end());
  }
  
  // Create graph
  int N = id;
  graph G(N);
  edge_adder adder(G);  
  
  // Connect consecutive time points
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < sortedTimePoints[j].size() - 1; ++i) {
      int t0 = sortedTimePoints[j][i];
      int t1 = sortedTimePoints[j][i + 1];
      adder.add_edge(timeToVertex[j][t0], timeToVertex[j][t1], sumCars, 100 * (t1 - t0));
    }
  }
  
  // Add edges for booking requests
  for (int i = 0; i < n; ++i) {
    adder.add_edge(timeToVertex[s[i]][d[i]], timeToVertex[t[i]][a[i]], 1, 100 * (a[i] - d[i]) - p[i]);
  }

  // Connect source and sink
  int source = boost::add_vertex(G);
  int target = boost::add_vertex(G);
  for (int j = 0; j < m; ++j) {
    adder.add_edge(source, timeToVertex[j][0], l[j], 0);
    adder.add_edge(timeToVertex[j][tMax], target, sumCars, 0);
  }

  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  int cost = boost::find_flow_cost(G);
  cost = 100 * sumCars * tMax - cost;

  cout << cost << endl;
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