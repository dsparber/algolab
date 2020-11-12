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

void solve()
{
    int buyers, sites, states;
    cin >> buyers >> sites >> states;

    graph G(states + sites + buyers);
    edge_adder adder(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);

    auto source = boost::add_vertex(G);
    auto target = boost::add_vertex(G);

    int stateLimit;
    for (int state = 0; state < states; ++state) {
        cin >> stateLimit;
        adder.add_edge(source, state, stateLimit, 0);
    }

    int state;
    int offsetSites = states;
    for (int site = offsetSites; site < offsetSites + sites; ++site) {
        cin >> state; --state; // convert to 0 based
        adder.add_edge(state, site, 1, 0);
    }

    int bid; 
    int maxBid = 100;
    int offsetBuyers = states + sites;
    for (int buyer = offsetBuyers; buyer < offsetBuyers + buyers; ++buyer) {
        for (int site = offsetSites; site < offsetSites + sites; ++site) {
            cin >> bid;
            adder.add_edge(site, buyer, 1, maxBid - bid); // Avoid negative costs
        }
        adder.add_edge(buyer, target, 1, 0);
    }

    boost::successive_shortest_path_nonnegative_weights(G, source, target);
    auto cost = boost::find_flow_cost(G);
    
    int flow = 0;
    out_edge_it e, eend;
    for (boost::tie(e, eend) = boost::out_edges(boost::vertex(source, G), G); e != eend; ++e)
    {
        flow += c_map[*e] - rc_map[*e];
    }
    cost = maxBid * flow - cost; // Convert back to actual cost

    cout << flow << " " << cost << endl;
}

int main()
{
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
