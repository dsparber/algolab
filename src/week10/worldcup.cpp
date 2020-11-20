#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> DT;

using namespace std;

// Annoying function for output
double floor_to_double(const CGAL::Quotient<ET>& x) {
    double a = floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a + 1 <= x) a += 1;
    return a;
}

void solve() {
    int n, m, c;
    cin >> n >> m >> c;

    // Read warehouses
    long x, y;
    vector<int> supply(n);
    vector<int> alcoholPercentage(n);
    vector<K::Point_2> warehouses(n);
    for (int i = 0; i < n; ++i) {
        cin >> x >> y >> supply[i] >> alcoholPercentage[i];
        warehouses[i] = K::Point_2(x, y);
    }

    // Read stadiums
    vector<int> demand(m);
    vector<int> upperAlcoholLimit(m);
    vector<K::Point_2> stadiums(m);
    for (int j = 0; j < m; ++j) {
        cin >> x >> y >> demand[j] >> upperAlcoholLimit[j];
        stadiums[j] = K::Point_2(x, y);
    }

    // Read revenues
    vector<vector<int>> revenue(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> revenue[i][j];
        }
    }


    // We have many contour lines, but only a few are relevant (i.e. at most 100). We only store those.
    // If a contour does not contain any relevant point (warehouse or stadium), it is irrelevant.
    // We find the closest relevant (with a DT) point and use the radius to check if it is inside the contour.
    DT dt;
    dt.insert(warehouses.begin(), warehouses.end());
    dt.insert(stadiums.begin(), stadiums.end());

    // Read contour lines
    long r;
    vector<K::FT> r2;
    vector<K::Point_2> contours;
    for (int i = 0; i < c; ++i) {
        cin >> x >> y >> r;
        K::Point_2 p(x, y);
        // Does it contain any stadium / warehouse?
        auto nearest = dt.nearest_vertex(p);
        if (CGAL::squared_distance(nearest->point(), p) <= K::FT(r * r)) {
            r2.emplace_back(r * r);
            contours.push_back(p);
        }
    }

    // For every contour, find contained warehouse and stadium. Save it.
    vector<set<int>> warehouseContours(n);
    vector<set<int>> stadiumContours(m);
    for (int k = 0; k < contours.size(); ++k) {
        for (int i = 0; i < n; ++i) {
            if (CGAL::squared_distance(warehouses[i], contours[k]) <= r2[k]) {
                warehouseContours[i].insert(k);
            }
        }
        for (int j = 0; j < m; ++j) {
            if (CGAL::squared_distance(stadiums[j], contours[k]) <= r2[k]) {
                stadiumContours[j].insert(k);
            }
        }
    }

    // Calculate profit based on revenue and on how many contour line are traversed.
    // The profit is multiplied by 100 to avoid rational numbers.
    vector<vector<int>> profit(n, vector<int>(m));;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            auto &a = warehouseContours[i];
            auto &b = stadiumContours[j];
            vector<int> its;
            set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(its));
            int t = a.size() + b.size() - 2 * its.size();
            profit[i][j] = revenue[i][j] * 100 - t;
        }
    }

    // Solve it with linear programming.
    // There is one variable for every warehouse-stadium pair.
    // A variable x_ij describes the amount of beer (liters) transported from warehouse i to stadium j.
    // All variables must obviously be positive.
    Program lp = Program(CGAL::SMALLER, true, 0, false, 0);

    // Warehouse constraints
    for (int i = 0; i < n; ++i) {
        // sum x_ij <= supply[i]
        lp.set_b(i, supply[i]);
        for (int j = 0; j < m; ++j) {
            int x_ij = i * m + j;
            lp.set_a(x_ij, i, 1);
        }
    }

    // Stadium constraints
    for (int j = 0; j < m; ++j) {
        // (1) sum x_ij <= demand
        // (2) sum x_ij >= demand <=> sum -x_ij <= -demand
        // (3) sum a_i / 100 * x_ij <= u <=> sum a_i * x_ij <= 100 * u

        int offset1 = n;
        int offset2 = offset1 + m;
        int offset3 = offset2 + m;

        lp.set_b(offset1 + j, demand[j]); // (1)
        lp.set_b(offset2 + j, -demand[j]); // (2)
        lp.set_b(offset3 + j, 100 * upperAlcoholLimit[j]); // (3)

        for (int i = 0; i < n; ++i) {
            int x_ij = i * m + j;
            lp.set_a(x_ij, offset1 + j, 1); // (1)
            lp.set_a(x_ij, offset2 + j, -1); // (2)
            lp.set_a(x_ij, offset3 + j, alcoholPercentage[i]); // (3)
        }
    }

    // max sum profit_ij * x_ij <=> min sum -profit_ij * x_ij
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x_ij = i * m + j;
            lp.set_c(x_ij, -profit[i][j]);
        }
    }

    // Solve it
    Solution solution = CGAL::solve_nonnegative_linear_program(lp, ET());

    if (solution.is_infeasible()) {
        cout << "RIOT!" << endl;
    } else { // Can not be unbounded as there is only a limited supply
        cout << fixed << setprecision(0) << floor_to_double(solution.objective_value() / ET(-100)) << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}