#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef int                                                    Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  DT;
typedef std::pair<K::Point_2,Index> IPoint;

using namespace std;

struct gangMember {
  int u, v, w;
};


// A straight forward LP with an additional Delaunay Triangulation 
// to figure out which agent is observing which gang member.
void solve() {
  
  int z, u, v, w;
  cin >> z >> u >> v >> w;
  
  int a, g;
  cin >> a >> g;
  
  // Read gang and construct DT of positions of gang members
  int x, y, ui, vi, wi;
  vector<gangMember> gang(g);
  vector<IPoint> pts(g);
  for (int i = 0; i < g; ++i) {
    cin >> x >> y >> ui >> vi >> wi;
    pts[i] = {{x, y}, i};
    gang[i] = {ui, vi, wi};
  }
  
  DT dt;
  dt.insert(pts.begin(), pts.end());

  // Read agents and assign them to observe a gang member.
  // To make things easier, we simply store the observation cost directly 
  // to the observed gang member.
  int zi;
  vector<int> observationCost(g, numeric_limits<int>::max());
  for (int i = 0; i < a; ++i) {
    cin >> x >> y >> zi;
    // An agent always observes the nearest gang member
    int nearest = dt.nearest_vertex(K::Point_2(x, y))->info();
    // If a gang member is observed by multiple agents, we want to use the cheapest agent
    observationCost[nearest] = min(zi, observationCost[nearest]);
  }

  // Solve a LP with the inequalites (1-3) and objective (4)
  // (1)  sum hi*ui >= u
  // (2)  sum hi*vi >= v
  // (3)  sum hi*wi >= w
  // (4)  min sum hi*zi
  Program lp (CGAL::LARGER, true, 0, true, 24); 
  
  lp.set_b(0, u); // (1)
  lp.set_b(1, v); // (2)
  lp.set_b(2, w); // (3)
  
  int hi = 0;
  for (int i = 0; i < g; ++i) {
    zi = observationCost[i];
    if (zi == numeric_limits<int>::max()) {
      continue; // This gang member is not observed by any agent
    }

    lp.set_a(hi, 0, gang[i].u); // (1)
    lp.set_a(hi, 1, gang[i].v); // (2)
    lp.set_a(hi, 2, gang[i].w); // (3)
    
    lp.set_c(hi, zi); // (4)
    
    hi++;
  }
  
  Solution solution = CGAL::solve_linear_program(lp, ET());
  
  // Holmes gets hired if the solution is infeasible or mor expensive than Holmes fee
  if (solution.is_infeasible() || solution.objective_value() > z) {
    cout << "H" << endl;
  }
  else {
    cout << "L" << endl;
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
