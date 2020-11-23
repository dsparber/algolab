#include <iostream>
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
                                                                              boost::property<boost::edge_weight_t, long>>>>>
    graph; // new! weightmap corresponds to costs
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it; // Iterator

// Custom edge adder class
class edge_adder
{
    graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}
    void add_edge(int from, int to, long capacity, long cost)
    {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        auto w_map = boost::get(boost::edge_weight, G); // new!
        const edge_desc e = boost::add_edge(from, to, G).first;
        const edge_desc rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
        w_map[e] = cost;      // new assign cost
        w_map[rev_e] = -cost; // new negative cost
    }
};

using namespace std;


// Idea:
// Train has l seats. 
// Each seat can either be occupied by an agent or a regular passenger.
// An agent on a mission brings reward q, a regular passenger 0.
// l people board the train
// At a given stop: 
// - either start mission to target-stop with value q
// - or travel to next stop without reward
void solve()
{
    int stops, missions, maxAgents;
    cin >> stops >> missions >> maxAgents;

    int maxValue = 128; // 2^7

    graph G(stops);
    edge_adder adder(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);

    auto source = boost::add_vertex(G);
    auto target = boost::add_vertex(G);

    adder.add_edge(source, 0, maxAgents, 0);
    adder.add_edge(stops - 1, target, maxAgents, 0);

    for (int stop = 0; stop < stops - 1; ++stop) {
        adder.add_edge(stop, stop + 1, maxAgents, maxValue);
    }

    int u, v, q;
    for (int mission = 0; mission < missions; ++mission) {
        cin >> u >> v >> q;
        adder.add_edge(u, v, 1, maxValue * (v - u) - q);
    }

    boost::successive_shortest_path_nonnegative_weights(G, source, target);
    auto cost = boost::find_flow_cost(G);
    cost = maxAgents * maxValue * (stops - 1) - cost;
    cout << cost << endl;
}

int main()
{
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
