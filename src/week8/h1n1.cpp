#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
        boost::no_property, boost::property<boost::edge_weight_t, long> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

typedef int Info;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT FT;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<Info, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;


using namespace std;

long findWidestPath(const int u, const vector<int> &predecessors, vector<long> &widestPath, const weight_map &w, const weighted_graph &G) {
    if (widestPath[u] == -1) {
        auto v = predecessors[u];
        auto e = boost::edge(u, v, G).first;
        widestPath[u] = min(numeric_limits<long>::max() - w[e], findWidestPath(predecessors[u], predecessors, widestPath, w, G));
    }
    return widestPath[u];
}

void solve(int n) {

    // List of infected people
    vector<K::Point_2> pts(n);

    long x, y;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        pts[i] = K::Point_2(x, y);
    }

    DT dt;
    dt.insert(pts.begin(), pts.end());

    // Assign ids to all faces, to later use them in a BGL graph
    int count = 0;
    for (auto f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
        f->info() = ++count;
    }

    n = count + 1;

    // We construct a graph of faces. Neighboring faces are connected with an edge.
    // We build a MST to make finding paths easier
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);

    for (auto f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
        auto u = f->info();
        for (int i = 0; i < 3; ++i) {
            int v = 0;
            if (!dt.is_infinite(f->neighbor(i))) {
              v = f->neighbor(i)->info();
            }
            auto p1 = f->vertex((i + 1) % 3)->point();
            auto p2 = f->vertex((i + 2) % 3)->point();

            // Extract long coordinates from points (to avoid constructions)
            auto dx = long(p1.x()) - long(p2.x());
            auto dy = long(p1.y()) - long(p2.y());

            long squaredDistance = dx * dx + dy * dy;

            // Negate distance to get max-spanning tree
            auto e = boost::add_edge(u, v, numeric_limits<long>::max() - squaredDistance, G);
        }
    }

    vector<long> widestPath(n, -1);
    widestPath[0] = numeric_limits<long>::max();

    std::vector<int> predecessors(n);
    boost::prim_minimum_spanning_tree(G, boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, G)), boost::root_vertex(0));
    vector<vector<int>> neighbors(n, vector<int>());
    for (int v = 0; v < n; ++v) {
        findWidestPath(v, predecessors, widestPath, weights, G);
    }

    int m;
    cin >> m;
    long d;
    for (int j = 0; j < m; ++j) {
        cin >> x >> y >> d;

        auto p = K::Point_2(x, y);
        auto nearest = dt.nearest_vertex(p);

        if (CGAL::squared_distance(p, nearest->point()) < FT(d)) {
            cout << "n";
            continue;
        }
        auto triangle = dt.locate(p);
        if (dt.is_infinite(triangle)) {
            cout << "y";
            continue;
        }

        int v = triangle->info();
        if (widestPath[v] >= 4 * d) {
            cout << "y";
        }
        else {
            cout << "n";
        }
    }
    cout << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    int n;
    while (cin >> n && n > 0) {
        solve(n);
    }
    return 0;
}