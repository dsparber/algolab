
#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpzf.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Gmpz IT; // input type
typedef CGAL::Gmpz ET; // exact type for solver

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

struct point {
    int x;
    int y;
    int z;
};

vector<IT> coefficients(point &p, int d) {
    auto x = p.x;
    auto y = p.y;
    auto z = p.z;
    vector<IT> coeff;
    IT powerX = 1;
    for (int i = 0; i <= d; ++i) {
        IT powerXY = powerX;
        for (int j = 0; j <= d - i; ++j) {
            IT powerXYZ = powerXY;
            for (int k = 0; k <= d - i - j; ++k) {
                coeff.push_back(powerXYZ);
                powerXYZ *= z;
            }
            powerXY *= y;
        }
        powerX *= x;   
    }
    return coeff;
}

bool isFeasible( vector<point> &A,  vector<point> &B, int d) {
    Program lp = Program(CGAL::SMALLER, false, 0, false, 0);

    int h = A.size();
    int t = B.size();

    const int epsilon = 0;

    for (int i = 0; i < h; ++i) {
        auto coeff = coefficients(A[i], d);
        lp.set_a(epsilon, i, 1);
        for (int j = 0; j < coeff.size(); ++j) {
            lp.set_a(j + 1, i, coeff[j]);
        }
    }
    for (int i = 0; i < t; ++i) {
        auto coeff = coefficients(B[i], d);
        lp.set_a(epsilon, h + i, 1);
        for (int j = 0; j < coeff.size(); ++j) {
            lp.set_a(j + 1, h + i, -coeff[j]);
        }
    }

    // Epsilon needs to be greater or equal 0
    lp.set_l(epsilon, true, 0);

    // maximize epsilon <=> minimize -epsilon
    lp.set_c(epsilon, -1);
    
    CGAL::Quadratic_program_options options;
    options.set_pricing_strategy(CGAL::QP_BLAND);

    Solution s = CGAL::solve_linear_program(lp, ET(), options);

    if (s.is_infeasible()) {
        return false;
    }

    if (s.is_unbounded()) {
        return true;
    }

    return s.objective_value() < 0;
}

void solve() {
    int h; cin >> h;
    int t; cin >> t;

    vector<point> A(h);
    vector<point> B(t);

    int x, y, z;
    for (int i = 0; i < h; ++i) {
        cin >> x >> y >> z;
        A[i] = {x, y, z};
    }
    for (int i = 0; i < t; ++i) {
        cin >> x >> y >> z;
        B[i] = {x, y, z};
    }
    
    for (int d = 0; d <= 30; ++d) {
      if (isFeasible(A, B, d)) {
        cout << d << endl;
        return;
      }
    }
    cout << "Impossible!" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}