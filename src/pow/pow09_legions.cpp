#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>

typedef int IT; // input type
typedef CGAL::Gmpz ET; // exact type for solver

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void solve() {
    int xs, ys, n;
    cin >> xs >> ys >> n;

    Program lp = Program(CGAL::SMALLER, false, 0, false, 0);

    int x = 0;
    int y = 1;
    int r = 2;

    long a, b, c, v;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b >> c >> v;

        long valStart = a * xs + b * ys + c;
        if (valStart > 0) {
            a *= -1;
            b *= -1;
            c *= -1;
        }

        long sqrtTerm = long(sqrt(a * a + b * b));
        
        lp.set_a(x, i, a);
        lp.set_a(y, i, b);
        lp.set_a(r, i, v * sqrtTerm);
        
        lp.set_b(i, -c);
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
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}