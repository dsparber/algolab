///1
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <vector>
#include <tuple>
#include <iostream>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
struct FaceInfo
{
    int id;
    K::FT r2;
};
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  DT;
typedef std::pair<K::Point_2,int> IPoint;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
        boost::no_property, boost::property<boost::edge_weight_t, K::FT> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

K::FT MAX_VALUE = K::FT(numeric_limits<long>::max()) * K::FT(numeric_limits<long>::max());

K::FT findWidestPath(const int u, const vector<int> &predecessors, vector<K::FT> &widestPath, const weight_map &w, const weighted_graph &G) {
    if (widestPath[u] == -1) {
        auto v = predecessors[u];
        auto e = boost::edge(u, v, G).first;
        widestPath[u] = min(MAX_VALUE - w[e], findWidestPath(predecessors[u], predecessors, widestPath, w, G));
    }
    return widestPath[u];
}

void solve() {
    int n, m;
    long r;

    cin >> n >> m >> r;

    long x, y;
    vector<IPoint> pts;
    pts.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        pts.emplace_back(K::Point_2(x, y), i);
    }

    DT dt;
    dt.insert(pts.begin(), pts.end());

    // Assign info to finite faces
    int id = 0;
    for (auto f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
        auto radius2 = CGAL::squared_distance(dt.dual(f), f->vertex(0)->point());
        f->info() = {++id, radius2};
    }
    int numVertices = id + 1;
    weighted_graph G(numVertices);
    weight_map weights = boost::get(boost::edge_weight, G);
    for (auto f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
        int u = f->info().id;
        for (int i = 0; i < 3; ++i) {
            auto p1 = f->vertex(i)->point();
            auto p2 = f->vertex((i + 1) % 3)->point();
            auto w = CGAL::squared_distance(p1, p2);

            auto neighbor = f->neighbor((i + 2) % 3);
            int v = dt.is_infinite(neighbor) ? 0 : neighbor->info().id;

            auto weight = MAX_VALUE - w;
            if (weight < 0) {
                cout << "error" << endl;
            }
            boost::add_edge(u, v, weight, G);
        }
        auto weight = MAX_VALUE - f->info().r2;
        if (weight < 0) {
            cout << "error" << endl;
        }
        boost::add_edge(u, 0, weight, G);
    }

    vector<K::FT> widestPath(numVertices, -1);
    widestPath[0] = MAX_VALUE;

    vector<int> predecessors(numVertices);
    boost::prim_minimum_spanning_tree(G, boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, G)), boost::root_vertex(0));
    for (int v = 1; v < numVertices; ++v) {
        findWidestPath(v, predecessors, widestPath, weights, G);
    }

    long s;
    for (int j = 0; j < m; ++j) {
        cin >> x >> y >> s;

        auto p = K::Point_2(x, y);
        auto nearest = dt.nearest_vertex(p);

        K::FT d = K::FT((r + s)) * K::FT((r + s));

        if (CGAL::squared_distance(p, nearest->point()) < d) {
            cout << "n";
            continue;
        }

        int v = dt.locate(p)->info().id;
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
    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}