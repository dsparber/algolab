#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <limits>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/connected_components.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef int Info;
typedef CGAL::Triangulation_vertex_base_with_info_2<Info,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> DT;
typedef Tds::Vertex_handle Vh;
typedef std::pair<K::Point_2,Info> IPoint;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

typedef std::vector <boost::default_color_type> partition_t;
typedef typename boost::property_map <graph, boost::vertex_index_t>::type index_map_t;
typedef boost::iterator_property_map <partition_t::iterator, index_map_t> partition_map_t;

using namespace std;


// Use the Delaunay Triangulation to find and add all vertices,
// that are closer than r 
void addAllInRange(Vh u, DT& dt, graph& G, K::FT& r2) {
    set<Vh> visited;
            
    vector<Vh> q;
    q.push_back(u);
    visited.insert(u);

    while (!q.empty()) {

        auto v = q[q.size() - 1];
        q.pop_back();

        if (u != v) {
            boost::add_edge(u->info(), v->info(), G);
        }

        auto neighbor = v->incident_vertices();
        do {
            if (!dt.is_infinite(neighbor) && visited.find(neighbor) == visited.end() && CGAL::squared_distance(u->point(), neighbor->point()) <= r2) {
                visited.insert(neighbor);
                q.push_back(neighbor);
            }
        } while(++neighbor != v->incident_vertices());
    }
}

void solve()
{
    int n, m;
    K::FT r;
    cin >> n >> m >> r;

    auto r2 = r * r;

    vector<IPoint> pts(n);
    long x, y;
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        pts[i] = {K::Point_2(x, y), i};
    }

    DT dt;
    dt.insert(pts.begin(), pts.end());


    // Construct graph of potentially conflicting stations 
    graph G(n);
    for (auto u = dt.finite_vertices_begin(); u != dt.finite_vertices_end(); ++u) {
        addAllInRange(u, dt, G, r2);
    }


    // Use BGL check for interference (no interference iff bipartit)
    auto is_bipartite = boost::is_bipartite(G);
    
    // Connected components: 
    std::vector<int> component_map(n);
    boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 

    int x1, x2, y1, y2;
    for (int j = 0; j < m; ++j)
    {
        cin >> x1 >> y1 >> x2 >> y2;

        if (!is_bipartite) {
            cout << "n";
            continue;
        }

        auto p1 = K::Point_2(x1, y1);
        auto p2 = K::Point_2(x2, y2);

        if (CGAL::squared_distance(p1, p2) <= r2) {
            cout << "y";
            continue;
        }

        auto v1 = dt.nearest_vertex(p1);
        auto v2 = dt.nearest_vertex(p2);

        if (CGAL::squared_distance(p1, v1->point()) > r2 || CGAL::squared_distance(p2, v2->point()) > r2 ) {
            cout << "n";
            continue;
        }

        if (component_map[v1->info()] == component_map[v2->info()]) {
            cout << "y";
        }
        else {
            cout << "n";
        }
    }
    cout << endl;

}

int main()
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        solve();
    }
    return 0;
}