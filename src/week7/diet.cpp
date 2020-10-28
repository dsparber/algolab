#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT; // input type
typedef CGAL::Gmpz ET; // exact type for solver

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void solve(int n, int m) {
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cin >> b[i];
    }
    vector<int> p(m);
    vector<vector<int>> c(m, vector<int>(n));
    for (int j = 0; j < m; ++j) {
        cin >> p[j];
        for (int i = 0; i < n; ++i) {
            cin >> c[j][i];
        }
    }
    
    const int x = 0;
    const int y = 1;
    const int z = 2;

    Program lp = Program(CGAL::SMALLER, true, 0, false, 0);

    for (int i = 0; i < n; ++i) {
        lp.set_b(i, b[i]); // xi <= b
        lp.set_b(i + n, -a[i]); // a <= xi <=> -xi <= -a

        for (int j = 0; j < m; ++j) {
            lp.set_a(j, i, c[j][i]);
            lp.set_a(j, i + n, -c[j][i]);
        }
    }

    for (int j = 0; j < m; ++j) {
        lp.set_c(j, p[j]);
    }

    Solution s = CGAL::solve_linear_program(lp, ET());

    if (s.is_infeasible()) {
        cout << "No such diet." << endl;
    } else {
        cout << setprecision(0) << fixed << floor(CGAL::to_double(s.objective_value())) << endl;
    }
}

int main() {
    int n, m;
    while (cin >> n) {
        cin >> m;
        solve(n, m);
    }
    return 0;
}