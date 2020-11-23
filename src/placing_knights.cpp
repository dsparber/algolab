#include <iostream>
#include <cmath>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>>
    graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder
{
    graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}

    void add_edge(int from, int to, long capacity)
    {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const auto e = boost::add_edge(from, to, G).first;
        const auto rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }

    void add_edge_if_exists(int i1, int j1, int i2, int j2, int n, std::vector<bool>& present) {
        int from = i1 * n + j1;
        int to = i2 * n + j2;
        if (i1 < 0 || i2 < 0 || j1 < 0 || j2 < 0 
            || i1 >= n || i2 >= n || j1 >= n || j2 >= n 
            || !present[from] || !present[to]) {
            return;
        }
        add_edge(from, to, 1);
    }
};

using namespace std;

void solve() {
    int n; cin >> n;

    graph G(n * n);
    edge_adder adder(G);

    auto source = boost::add_vertex(G);
    auto target = boost::add_vertex(G);


    bool p;
    vector<bool> present(n * n, false);
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> p;
            present[i * n + j] = p;

            if (!p) {
                continue;
            }

            ++count;

            int parity = (i + j) % 2;
            if (parity == 0) {
                adder.add_edge(source, i * n + j, 1);
            }
            else {
                adder.add_edge(i * n + j, target, 1);
            }
        }
    }

    // Build conflict graph
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int parity = (i + j) % 2;
            if (parity == 1) {
                continue;
            }
            adder.add_edge_if_exists(i, j, (i - 1), (j - 2), n, present);
            adder.add_edge_if_exists(i, j, (i - 1), (j + 2), n, present);
            adder.add_edge_if_exists(i, j, (i + 1), (j - 2), n, present);
            adder.add_edge_if_exists(i, j, (i + 1), (j + 2), n, present);
            adder.add_edge_if_exists(i, j, (i - 2), (j - 1), n, present);
            adder.add_edge_if_exists(i, j, (i - 2), (j + 1), n, present);
            adder.add_edge_if_exists(i, j, (i + 2), (j - 1), n, present);
            adder.add_edge_if_exists(i, j, (i + 2), (j + 1), n, present);
        }
    }


    long maxFlow = boost::push_relabel_max_flow(G, source, target);
    long maxMatching = maxFlow;
    long minVC = maxMatching;
    long maxIS = count - minVC;

    cout << maxIS << endl;
}

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
}