#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT; // input type
typedef CGAL::Gmpz ET; // exact type for solver

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void solve(int n, int d) {

    Program lp = Program(CGAL::SMALLER, false, 0, false, 0);

    const int r = d;

    // a.dot(c) + ||a||r <= b
    int aij, bi, norm;
    for (int i = 0; i < n; ++i) {
        norm = 0;
        for (int j = 0; j < d; ++j) {
            cin >> aij;
            norm += aij * aij;
            lp.set_a(j, i, aij);
        }
        norm = sqrt(norm);
        lp.set_a(r, i, norm);
        
        cin >> bi;
        lp.set_b(i, bi);
    }

    // Radius needs to be positive
    lp.set_l(r, true, 0);

    // Maximize radius
    lp.set_c(r, -1);
    
    Solution s = CGAL::solve_linear_program(lp, ET());

    if (s.is_infeasible()) {
        cout << "none" << endl;
    }
    else if (s.is_unbounded()) {
        cout << "inf" << endl;
    }
    else {
        // Implicit round down due to integer division
        cout << - s.objective_value_numerator() / s.objective_value_denominator() << endl;
    }
}

int main() {
    int n, d;
    while (cin >> n && n > 0) {
        cin >> d;
        solve(n, d);
    }
    return 0;
}