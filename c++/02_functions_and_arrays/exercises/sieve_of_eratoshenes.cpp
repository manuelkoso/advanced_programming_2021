#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void sieve_algo(int n) {
  vector<bool> a;
  for (int i{0}; i <= n; ++i) {
    a.push_back(true);
  }

  for (int i = 2; i < sqrt(n); i++) {
    if (a.at(i)) {
      for (int j = i * i + i; j < n; j = j + i) {
        a.at(j) = false;
      }
    }
  }

  for (int i = 0; i < a.size(); ++i) {
    if (a.at(i)) {
      cout << i << " ";
    }
  }

  cout << endl;
}

int main() {
  int n;

  cin >> n;

  sieve_algo(n);

  return 0;
}