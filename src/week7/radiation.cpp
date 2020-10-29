#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
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
    auto x = IT(p.x);
    auto y = IT(p.y);
    auto z = IT(p.z);
    vector<IT> coeff;
    IT powerX = 1;
    for (int i = 0; i <= d; ++i) {
        IT powerY = 1;
        for (int j = 0; j <= d - i; ++j) {
            IT powerZ = 1;
            for (int k = 0; k <= d - i - j; ++k) {
                coeff.push_back(powerX * powerY * powerZ);
                powerZ *= z;
            }
            powerY *= y;
        }
        powerX *= x;   
    }
    return coeff;
}

bool isFeasible( vector<point> &A,  vector<point> &B, int d) {
    Program lp = Program(CGAL::SMALLER, false, 0, false, 0);

    auto h = A.size();
    auto t = B.size();

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

    Solution s = CGAL::solve_linear_program(lp, ET());

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
        cin >> x;
        cin >> y;
        cin >> z;
        A[i] = point({x, y, z});
    }
    for (int i = 0; i < t; ++i) {
        cin >> x;
        cin >> y;
        cin >> z;
        B[i] = point({x, y, z});
    }

    // Binary search for d
    int a = 0;
    int b = 30;

    int minD = -1;
    while (a <= b) {
        int d = (a + b + 1) / 2;
        if (!isFeasible(A, B, d)) {
            a = d + 1;
        }
        else {
            minD = d;
            b = d - 1;
        }
    }
    if (minD == -1) {
        cout << "Impossible!" << endl;
    }
    else {
        cout << minD << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}