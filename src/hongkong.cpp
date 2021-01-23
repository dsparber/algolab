#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <queue>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::FT FT;
struct FaceInfo {
    int id;
    FT r2;
};
struct Neighbor {
  int vertex;
  FT width;
};

typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  DT;
typedef std::pair<K::Point_2,int> IPoint;

using namespace std;

FT MAX_VALUE = FT(numeric_limits<long>::max()) * FT(numeric_limits<long>::max());

void solve() {
    int n, m;
    long r;

    cin >> n >> m >> r;

    // Construct Delaunay triangulation
    DT dt;
    long x, y;
    vector<IPoint> pts;
    pts.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        pts.emplace_back(K::Point_2(x, y), i);
    }
    dt.insert(pts.begin(), pts.end());


    // Assign info to finite faces
    int id = 0;
    for (auto f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
        FT radius2 = CGAL::squared_distance(dt.dual(f), f->vertex(0)->point());
        f->info() = {++id, radius2};
    }

    // Create edges between adjacent faces
    vector<vector<Neighbor>> neighbors(id + 1);
    for (auto f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
        int u = f->info().id;

        // Connect neighbors
        for (int i = 0; i < 3; ++i) {
            auto neighbor = f->neighbor((i + 2) % 3);
            int v = dt.is_infinite(neighbor) ? 0 : neighbor->info().id;

            auto p1 = f->vertex(i)->point();
            auto p2 = f->vertex((i + 1) % 3)->point();
            FT width = CGAL::squared_distance(p1, p2);
            neighbors[u].push_back({v, width});
            neighbors[v].push_back({u, width});
        }

        // Connect to outside (balloon take-off)
        FT width = f->info().r2;
        neighbors[u].push_back({0, width});
        neighbors[0].push_back({u, width});
    }

    // Find widest path width a modified Dijkstra
    vector<FT> widestPath(id + 1, -1);

    priority_queue<tuple<FT, int>> q;
    q.push({MAX_VALUE, 0});

    while (!q.empty()) {
        int u = get<1>(q.top());
        FT maxWidth = get<0>(q.top());
        q.pop();

        if (widestPath[u] != -1) {
            continue;
        }
        widestPath[u] = maxWidth;

        for (auto &neighbor : neighbors[u]) {
            int v = neighbor.vertex;
            FT width = neighbor.width;
            if (widestPath[v] == -1) {
                FT neighborMaxWidth = min(widestPath[u], width);
                q.push({neighborMaxWidth, v});
            }
        }
    }
    
    // Queries
    long s;
    for (int j = 0; j < m; ++j) {
        cin >> x >> y >> s;

        auto p = K::Point_2(x, y);
        auto nearest = dt.nearest_vertex(p);

        FT d = (FT(r) + FT(s)) * (FT(r) + FT(s));

        // Balloon is too large for initial position
        if (CGAL::squared_distance(p, nearest->point()) < d) {
            cout << "n";
            continue;
        }

        auto face = dt.locate(p);
        if (dt.is_infinite(face)) {
            cout << "y";
            continue;
        }

        // Find widest path
        int v = face->info().id;
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