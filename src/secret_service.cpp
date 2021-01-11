#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

// For dijkstra
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;


// For max flow
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

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

// Compute shortest distances
void dijkstra(const weighted_graph &G, int s, vector<int>& dist_map) {
  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
}

// Is it possible for all agents to seek shelter for a given tMax?
bool isFeasible(vector<vector<int>>& timeToShelter, int capacity, int timeToEnter, int tMax) {
  int a = timeToShelter.size();
  int s = timeToShelter[0].size();
  
  graph G(a + capacity * s + 2);
  edge_adder adder(G);
  int source = a + capacity * s;
  int target = source + 1;
  
  for (int i = 0; i < a; ++i) { 
    adder.add_edge(source, i, 1);
  }
  
  for (int j = 0; j < s; ++j) { 
    for (int c = 1; c <= capacity; ++c) {
      adder.add_edge(a + (c - 1) * s + j, target, 1);
    }
  }
   
  
  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < s; ++j) {
      for (int c = 1; c <= capacity; ++c) {
        if (timeToShelter[i][j] <= tMax - c * timeToEnter) {
          adder.add_edge(i, a + (c - 1) * s + j, 1);
        }
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, source, target);
  return flow == a;
}

// Use binary search to find the smallest t such that (isFeasible(t) == True)
void solve() {
    
    int n, m, a, s, c, d;
    cin >> n >> m >> a >> s >> c >> d;
    
    // Read skiing area
    weighted_graph G(n);
    char w;
    int x, y, z;
    for (int i = 0; i < m; ++i) {
      cin >> w >> x >> y >> z;
      
      boost::add_edge(x, y, z, G);
      if (w == 'L') {
         boost::add_edge(y, x, z, G);
      }
    }
    
    // Read agent positions
    vector<int> agents(a);
    for (int i = 0; i < a; ++i) {
      cin >> agents[i];
    }
    
    // Read shelter positions
    vector<int> shelters(s);
    for (int j = 0; j < s; ++j) {
      cin >> shelters[j];
    }
    
    vector<vector<int>> distToShelter(a, vector<int>(s)); 
    for (int i = 0; i < a; ++i) {
      vector<int> dist_map(n);
      dijkstra(G, agents[i], dist_map);
      for (int j = 0; j < s; ++j) {
        distToShelter[i][j] = dist_map[shelters[j]];
      }
    }
    
    int low = 1;
    int high = numeric_limits<int>::max() - 1;
    
    while (low != high) {
      int t = low + (high - low) / 2;
      if (isFeasible(distToShelter, c, d, t)) {
        high = t;   
      }
      else {
        low = t + 1;
      }
    }
    
    cout << low << endl;
  
}

int main()
{
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
