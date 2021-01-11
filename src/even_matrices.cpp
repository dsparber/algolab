#include <iostream>
#include <vector>
using namespace std;

int testcase() {
  int n; cin >> n;
  vector<vector<int>> in;
  vector<vector<int>> sum;
  in.push_back(vector<int>());
  sum.push_back(vector<int>());
  for (int i = 0; i <= n; ++i) {
    in[0].push_back(0);
    sum[0].push_back(0);
  }
  for (int i = 1; i <= n; ++i) {
    in.push_back(vector<int>());
    in[i].push_back(0);
    sum.push_back(vector<int>());
    sum[i].push_back(0);
    for (int j = 1; j <= n; ++j) {
      int x; cin >> x;
      int cellSum = x + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
      in[i].push_back(x);
      sum[i].push_back(cellSum);
    }
  }
  
  vector<vector<int>> even;
  vector<vector<int>> odd;
  even.push_back(vector<int>());
  odd.push_back(vector<int>());
  for (int i = 0; i <= n; ++i) {
    even[0].push_back(0);
    odd[0].push_back(0);
  }
  for (int i = 1; i <= n; ++i) {
    even.push_back(vector<int>());
    odd.push_back(vector<int>());
    even[i].push_back(0);
    odd[i].push_back(0);
    for (int j = 1; j <= n; ++j) { 
      int oddCount = odd[i][j - 1] + odd[i - 1][j] - odd[i - 1][j - 1];
      int possibleSubmatrices = i * (i + 1) * j * (j + 1) / 4;
      
      
      if (sum[i][j] % 2 == 1) {
        ++oddCount;
      }
      
      if (sum[i][j] % 2 == 0) { // Even
        //oddCount += odd[i][j-1] + odd[i-1][j] - odd[i-1][j-1];
        int countIfs = 0;
        if (sum[i][j-1] != sum[i][j]) {
          oddCount += odd[i][j-1];
          ++countIfs;
        }
        if (sum[i-1][j] != sum[i][j]) {
          oddCount += odd[i-1][j];
          ++countIfs;
        }
        if (countIfs == 2) {
          oddCount -= odd[i-1][j-1];
        }
      }
      else { // Odd
        //oddCount += even[i][j-1] + even[i-1][j] - even[i-1][j-1];
        int countIfs = 0;
        if (sum[i][j-1] != sum[i][j]) {
          oddCount += even[i][j-1];
          ++countIfs;
        }
        if (sum[i-1][j] != sum[i][j]) {
          oddCount += even[i-1][j];
          ++countIfs;
        }
        if (countIfs == 2) {
          oddCount -= even[i-1][j-1];
        }
      }
  
      
      odd[i].push_back(oddCount);
      even[i].push_back(possibleSubmatrices - oddCount);
    }
  }
  cout << "in" << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << in[i][j] << "\t";
    }
    cout << endl;
  }
  cout << "sum" << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << sum[i][j] << "\t";
    }
    cout << endl;
  }
  cout << "even" << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << even[i][j] << "\t";
    }
    cout << endl;
  }
  cout << "odd" << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << odd[i][j] << "\t";
    }
    cout << endl;
  }
  
  return even[n][n];
  
  
  //vector<vector<int>> even;
  //vector<vector<int>> odd;
  even.push_back(vector<int>());
  odd.push_back(vector<int>());
  for (int i = 0; i <= n; ++i) {
    even[0].push_back(0);
    odd[0].push_back(0);
  }
  for (int i = 1; i <= n; ++i) {
    even.push_back(vector<int>());
    odd.push_back(vector<int>());
    even[i].push_back(0);
    odd[i].push_back(0);
    for (int j = 1; j <= n; ++j) { 
      int evenCount = even[i][j - 1] + even[i - 1][j] - even[i - 1][j - 1];
      int possibleSubmatrices = i * (i + 1) * j * (j + 1) / 4;
      if (sum[i][j] % 2 == 0) {// Even
        evenCount += 1;
        if (sum[i][j-1] % 2 == 0 && sum[i][j-1] != sum[i][j]) {
          evenCount += even[i][j-1];
        }
        if (sum[i-1][j] % 2 == 0  && sum[i-1][j] != sum[i][j]) {
          evenCount += even[i-1][j];
        }
        if (sum[i][j-1] % 2 == 0 && sum[i-1][j] % 2 == 0) {
          evenCount -= even[i-1][j-1];
        }
      }
      else { // Odd
        if (in[i][j] % 2 == 0) {
          evenCount += 1;
        }
        int countIfs = 0;
        if (sum[i][j-1] % 2 == 1 && sum[i][j-1] != sum[i][j]) {
          evenCount += odd[i][j-1];
          ++countIfs;
        }
        if (sum[i-1][j] % 2 == 1 && sum[i-1][j] != sum[i][j]) {
          evenCount += odd[i-1][j];
          ++countIfs;
        }
        if (countIfs == 2) {
          evenCount -= odd[i-1][j-1];
        }
      }
      // Even col or even row
      if ((sum[i][j] - sum[i-1][j]) % 2 == 0 && i > 1 && j > 1) {
        evenCount += 1;
      }
      if ((sum[i][j] - sum[i][j-1]) % 2 == 0 && i > 1 && j > 1) {
        evenCount += 1;
      }
      
      even[i].push_back(evenCount);
      odd[i].push_back(possibleSubmatrices - evenCount);
    }
  }
  cout << "in" << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << in[i][j] << "\t";
    }
    cout << endl;
  }
  cout << "sum" << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << sum[i][j] << "\t";
    }
    cout << endl;
  }
  cout << "even" << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << even[i][j] << "\t";
    }
    cout << endl;
  }
  cout << "odd" << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << odd[i][j] << "\t";
    }
    cout << endl;
  }
  
  return even[n][n];
  int count = 0;
  for (int i1 = 1; i1 <= n; ++i1) {
    for (int j1 = 1; j1 <= n; ++j1) {
      for (int i2 = i1; i2 <= n; ++i2) {
        for (int j2 = j1; j2 <= n; ++j2) {
          int value = sum[i1 - 1][j1 - 1] + sum[i2][j2] - sum[i1 - 1][j2] - sum[i2][j1 - 1];
          if (value % 2 == 0) {
            ++count;
          }
        }
      }
    }
  }
  return count;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    int solution = testcase();
    cout << solution << endl;
  }
}