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
  int cols; cin >> cols;
  int rows; cin >> rows;
  
  graph G;
  edge_adder adder(G);
  
  int targetFlow = 0;
  vertex_desc source = boost::add_vertex(G);
  vertex_desc target = boost::add_vertex(G);

  vector<vector<vertex_desc>> in(rows, vector<vertex_desc>(cols));
  vector<vector<vertex_desc>> out(rows, vector<vertex_desc>(cols));
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      in[row][col] = boost::add_vertex(G);
      out[row][col] = boost::add_vertex(G);
    }
  }
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      char c; cin >> c;
      bool blocked = (c == 'x');
      if (blocked) {
        continue;
      }
      bool even = (row + col) % 2 == 0;
      if (even) {
        adder.add_edge(source, in[row][col], 1);
        
        if (row > 0)
          adder.add_edge(in[row][col], out[row - 1][col], 1);
        if (row < rows - 1)
          adder.add_edge(in[row][col], out[row + 1][col], 1);
        if (col > 0)
          adder.add_edge(in[row][col], out[row][col - 1], 1);
        if (col < cols - 1)
          adder.add_edge(in[row][col], out[row][col + 1], 1);
      }
      else {
        adder.add_edge(out[row][col], target, 1);
      }
      ++targetFlow;
    }
  }
  if (targetFlow % 2 != 0) {
    cout << "no" << endl;
    return;
  }
  targetFlow /= 2;
  
  long flow = boost::push_relabel_max_flow(G, source, target);
  cout << ((flow == targetFlow) ? "yes" : "no") << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}