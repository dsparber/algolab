// STL includes
#include <iostream>
#include <vector>
#include <set>
#include <string>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

bool perfect_matching(const graph &G) {
  int n = boost::num_vertices(G);
  vector<vertex_desc> mate_map(n);  // exterior property map

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  return 2 * matching_size == n;
}

void solve() {
  
  int n; cin >> n;
  int c; cin >> c;
  unsigned int f; cin >> f;
  
  graph G(n);

  string x;
  vector<set<string>> ch(n, set<string>());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < c; ++j) {
      cin >> x;
      ch[i].insert(x);
    }
  }
  
  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
        vector<string> intersection;
        set_intersection(ch[i].begin(), ch[i].end(), ch[j].begin(), ch[j].end(), back_inserter(intersection));
        if (intersection.size() > f) {
            boost::add_edge(i, j, G);
        }
    }
  }

  cout << (perfect_matching(G) ? "not optimal" : "optimal") << endl;
}

int main()
{
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}