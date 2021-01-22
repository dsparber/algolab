// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

namespace boost {
    struct edge_component_t {
        enum { num = 555 };
        typedef edge_property_tag kind;
    } edge_component;
}

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_component_t, std::size_t >> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;


using namespace std;

struct edge {
    int u;
    int v;

    bool operator<(edge &o) const {
        return u < o.u || (u == o.u && v < o.v);
    }
};

void solve() {
    int n;
    cin >> n;
    int m;
    cin >> m;

    graph G(n);

    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u;
        cin >> v;
        boost::add_edge(u, v, G);
    }


    boost::property_map<graph, boost::edge_component_t>::type component = get(boost::edge_component, G);
    int ncc = biconnected_components(G, component);

    vector<vector<edge_desc>> edgesOfComponent(ncc, vector<edge_desc>());

    boost::graph_traits<graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei) {
        edgesOfComponent[component[*ei]].push_back(*ei);
    }

    vector<edge> result;
    for (int i = 0; i < ncc; ++i) {
        if (edgesOfComponent[i].size() == 1) {
            u = source(edgesOfComponent[i][0], G);
            v = target(edgesOfComponent[i][0], G);
            if (v < u) {
                u = target(edgesOfComponent[i][0], G);
                v = source(edgesOfComponent[i][0], G);
            }
            result.push_back({u, v});
        }
    }
    sort(result.begin(), result.end());

    cout << result.size() << endl;
    for (auto e : result) {
        cout << e.u << " " << e.v << endl;
    }
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
}