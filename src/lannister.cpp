#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void solve()
{
  int n; // Number of nobel houses
  int m; // Number of common houses
  long s; // Maximum allowable sum of lengths of all sewage pipes, -1 means unbounded
  
  cin >> n >> m >> s;
  
  vector<int> nx(n); // x coordinates of nobel houses
  vector<int> ny(n); // y coordinates of nobel houses
  long nxSum = 0;
  long nySum = 0;
  for (int i = 0; i < n; ++i) {
    cin >> nx[i] >> ny[i];
    nxSum += nx[i];
    nySum += ny[i];
  }
  
  vector<int> cx(m); // x coordinates of common houses
  vector<int> cy(m); // y coordinates of common houses
  long cxSum = 0;
  long cySum = 0;
  for (int i = 0; i < m; ++i) {
    cin >> cx[i] >> cy[i];
    cxSum += cx[i];
    cySum += cy[i];
  }
  
  // Solve it as a linear program
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  const int a = 0;
  const int b = 1;
  const int c = 2;
  const int d = 3;
  const int l = 4;

  int row = 0;

  // Nobel houses need to left of l1: ax + by + c
  for (int i = 0; i < n; ++i) {
    // ax + by + c <= 0
    lp.set_a(a, row, nx[i]); 
    lp.set_a(b, row, ny[i]);
    lp.set_a(c, row, 1);
    ++row;
  }
  
  // Common houses need to right of l1
  for (int i = 0; i < m; ++i) {
    // ax + by + c >= 0   <=>  -ax -by -c <= 0
    lp.set_a(a, row, -cx[i]); 
    lp.set_a(b, row, -cy[i]);
    lp.set_a(c, row, -1);
    ++row;
  }
  
  // enforce a != 0 by setting a == 1 
  lp.set_l(a, true, 1);
  lp.set_u(a, true, 1);
  
  
  // Solve the LP
  Solution solution = CGAL::solve_linear_program(lp, ET());

  if (solution.is_infeasible()) {
    cout << "Yuck!" << endl;
    return;
  }
  
  // Check Tywin's constraint
  // The sum of the lengths of all sewage pipes must not exceed s
  if (s != -1) {
    lp.set_a(b, row, cySum - nySum);
    lp.set_a(c, row, m - n);
    lp.set_b(row, s - (cxSum - nxSum));
    row++;
    
    solution = CGAL::solve_linear_program(lp, ET());

    if (solution.is_infeasible()) {
      cout << "Bankrupt!" << endl;
      return;
    }
  }
  
  // Jamie's optimization:
  // Minimize the length l of the longest fresh water pipe
  for (int i = 0; i < n; ++i) {
    // length of fresh pipe <= l
    lp.set_a(b, row, nx[i]);
    lp.set_a(d, row, 1);
    lp.set_a(l, row, -1);
    lp.set_b(row, ny[i]);
    row++;
    lp.set_a(b, row, -nx[i]);
    lp.set_a(d, row, -1);
    lp.set_a(l, row, -1);
    lp.set_b(row, -ny[i]);
    row++;
  }
  for (int i = 0; i < m; ++i) {
    // length of fresh pipe <= l
    lp.set_a(b, row, cx[i]);
    lp.set_a(d, row, 1);
    lp.set_a(l, row, -1);
    lp.set_b(row, cy[i]);
    row++;
    lp.set_a(b, row, -cx[i]);
    lp.set_a(d, row, -1);
    lp.set_a(l, row, -1);
    lp.set_b(row, -cy[i]);
    row++;
  }
  
  // Ensure l is positive
  lp.set_l(l, true, 0);
  
  // Minimize l
  lp.set_c(l, 1);
  
  solution = CGAL::solve_linear_program(lp, ET());
  
  cout << fixed << setprecision(0) << ceil(CGAL::to_double(solution.objective_value())) << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}