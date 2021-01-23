// From the official solution
#include <iostream>
#include <vector>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void testcase() {
  int n;
  std::cin >> n;

  // Input matrix
  VVI M = VVI(n + 1, VI(n + 1));
  // pm[i][j] = sum of elements in the submatrix (1, 1, i, j)
  VVI pM = VVI(n + 1, VI(n + 1));

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      std::cin >> M[i][j];


  for (int i = 0; i <= n; ++i) {
    pM[0][i] = 0;
    pM[i][0] = 0;
  }


  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      pM[i][j] = pM[i - 1][j] + pM[i][j - 1] - pM[i - 1][j - 1] + M[i][j];


  int solution = 0;

  for (int i1 = 1; i1 <= n; ++i1) {
    for (int i2 = i1; i2 <= n; ++i2) {

      // We reduce the problem to one dimension.
      VI S(201); // We do Even Pairs on array S.
      VI pS(201); // pS contains partial sums of S.
      pS[0] = 0;

      for (int k = 1; k <= n; ++k) {
        S[k] = pM[i2][k] - pM[i2][k - 1] - pM[i1 - 1][k] + pM[i1 - 1][k - 1];
        pS[k] = pS[k - 1] + S[k];
      }

      // Do Even Pairs O(n) algorithm on array S.
      // even = number of partial sums of array that are even.
      // odd = number of partial sums of array that are odd.
      int even = 0, odd = 0;
      for (int j = 1; j <= n; ++j) {
        if (pS[j] % 2 == 0) ++even;
        else ++odd;
      }

      solution += even * (even - 1) / 2;
      solution += odd * (odd - 1) / 2;
      solution += even;
    }
  }

  std::cout << solution << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
