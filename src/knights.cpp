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

int index(int row, int col, bool in, int cols) {
  return 2 * (row * cols + col) + in;
}

void solve() {
  int cols; cin >> cols;
  int rows; cin >> rows;
  int k; cin >> k;
  int c; cin >> c;
  
  graph G(2 * rows * cols);
  edge_adder adder(G);
  
  if (cols == 0 || rows == 0 || k == 0 || c == 0) {
    cout << 0 << endl;
    return;
  } 
  
  // Set up graph
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      // In to out vertex
      adder.add_edge(index(row, col, true, cols), index(row, col, false, cols), c);
      
      // Neighbors
      if (row > 0)
        adder.add_edge(index(row - 1, col, false, cols), index(row, col, true, cols), 1);
      if (row < rows - 1)
        adder.add_edge(index(row + 1, col, false, cols), index(row, col, true, cols), 1);
      if (col > 0)
        adder.add_edge(index(row, col - 1, false, cols), index(row, col, true, cols), 1);
      if (col < cols - 1)
        adder.add_edge(index(row, col + 1, false, cols), index(row, col, true, cols), 1);

    }
  }
  
  // Set up target
  vertex_desc target = boost::add_vertex(G);
  for (int row = 0; row < rows; ++row) {
    adder.add_edge(index(row, 0, false, cols), target, 1);
    adder.add_edge(index(row, cols - 1, false, cols), target, 1);
  }
  for (int col = 0; col < cols; ++col) {
    adder.add_edge(index(0, col, false, cols), target, 1);
    adder.add_edge(index(rows - 1, col, false, cols), target, 1);
  }
  
  // Set up source
  vertex_desc source = boost::add_vertex(G);
  int row, col;
  for (int i = 0; i < k; ++i) {
    cin >> col;
    cin >> row;
    adder.add_edge(source, index(row, col, true, cols), 1);
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