#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT; // input type
typedef CGAL::Gmpz ET; // exact type for solver

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void solve(int p) {
    int a, b;
    cin >> a;
    cin >> b;

    const int x = 0;
    const int y = 1;
    const int z = 2;

    if (p == 1) {
        Program lp = Program(CGAL::SMALLER, true, 0, false, 0);
        lp.set_a(x, 0, 1); lp.set_a(y, 0, 1); lp.set_b(0, 4); // x + y <= 4
        lp.set_a(x, 1, 4); lp.set_a(y, 1, 2); lp.set_b(1, a * b); // 4x + 2y <= ab
        lp.set_a(x, 2, -1); lp.set_a(y, 2, 1); lp.set_b(2, 1); // -x + y <= 1

        // max by - ax <=> min -(by - ax) = ax - by
        lp.set_c(x, a);
        lp.set_c(y, -b);

        Solution s = CGAL::solve_linear_program(lp, ET());

        if (s.is_infeasible()) {
            cout << "no" << endl;
        } else {
            cout << setprecision(0) << fixed << floor(CGAL::to_double(-s.objective_value())) << endl;
        }
    }
    else {
        Program lp = Program(CGAL::SMALLER, false, 0, true, 0);
        lp.set_a(x, 0, -1); lp.set_a(y, 0, -1); lp.set_b(0, 4); // -x - y <= 4
        lp.set_a(x, 1, -4); lp.set_a(y, 1, -2); lp.set_a(z, 1, -1); lp.set_b(1, a * b); // -4x - 2y - z <= ab
        lp.set_a(x, 2, 1); lp.set_a(y, 2, -1); lp.set_b(2, 1); // x - y <= 1

        // min ax + by + z
        lp.set_c(x, a);
        lp.set_c(y, b);
        lp.set_c(z, 1);

        Solution s = CGAL::solve_linear_program(lp, ET());
        if (s.is_infeasible()) {
            cout << "no" << endl;
        } else {
            cout << setprecision(0) << fixed << ceil(CGAL::to_double(s.objective_value())) << endl;
        }
    }


}

int main() {
    int p;
    while (cin >> p) {
        solve(p);
    }
    return 0;
}