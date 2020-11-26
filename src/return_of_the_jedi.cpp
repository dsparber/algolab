#include <iostream>
#include <vector>
#include <limits>
#include <cmath> 

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/pending/disjoint_sets.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

// Essentially, the tasks asks for the cost of the second best spanning tree.
// Leia performs Prims MST algorithm. We need at least one edge different to the MST,
// therefore, the best we can do is computing the second best spanning tree.
void solve() {
  // Tatooine is not needed for anything
  int n, tatooine;
  cin >> n >> tatooine;
  
  // Compute a MST (with any algorithm)
  weighted_graph G(n);

  int cost;
  vector<vector<int>> costs(n, vector<int>(n));
  for (int j = 0; j < n - 1; ++j) {
    for (int k = 0; k < n - j - 1; ++k) {
      int u = j;
      int v = j + k + 1;
      cin >> cost;
      costs[u][v] = cost;
      costs[v][u] = cost;
      boost::add_edge(u, v, cost, G);
    }
  }
  
  // Use Kurskal (we could also use Prim...does not make any difference)
  std::vector<edge_desc> mst;
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  
  // Extract neighbors from MST and compute MST Value
  int mstValue = 0;
  vector<vector<int>> neighbors(n);
  vector<vector<int>> isMstEdge(n, vector<int>(n, false));
  for (auto edge : mst) {
    int u = boost::source(edge, G);
    int v = boost::target(edge, G);
    mstValue += costs[u][v];
    neighbors[u].push_back(v);
    neighbors[v].push_back(u);
    isMstEdge[u][v] = true;
    isMstEdge[v][u] = true;
  }
  
  // Compute the most expensive edge for every u-v path in the MST
  vector<vector<int>> uvMaxEdge(n, vector<int>(n, 0));
  
  for (int u = 0; u < n; ++u) {
    vector<int> stack;
    stack.push_back(u);
    vector<int> visited(n, false);
    visited[u] = true;
  
    while (!stack.empty()) {
      int v = *stack.rbegin();
      stack.pop_back();
      
      for (auto w : neighbors[v]) {
        if (!visited[w]) {
          visited[w] = true;
          uvMaxEdge[u][w] = max(costs[v][w], uvMaxEdge[u][v]);
          stack.push_back(w);
        }
      }
    }
  }
  
  // For all edges e = {u, v}, that are not in the MST, we will try adding e to the MST.
  // This will introduce a cycle. We remove the most expensive edge of the cycle that is 
  // part of the MST. For this we can simply query the most expensive edge from u to v in the MST 
  // and remove it. The cost of the MST changes by delta = cost[u][v] - cost[most expensive edge].
  // We simply find the best delta.
  int minVal = numeric_limits<int>::max();
  for (int u = 0; u < n; ++u) {
    for (int v = u + 1; v < n; ++v) {
      if (!isMstEdge[u][v]) {
        int val = costs[u][v] - uvMaxEdge[u][v];
        minVal = min(val, minVal);
      }
    }
  }
  
  cout << mstValue + minVal << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) {
    solve();
  }
}