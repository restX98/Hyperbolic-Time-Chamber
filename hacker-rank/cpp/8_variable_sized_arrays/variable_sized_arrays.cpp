#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {

  int n, q;

  cin >> n >> q;

  vector<int> a[n];

  int k;
  for (int c = 0; c < n; c++) {
    cin >> k;

    a[c] = vector<int>(k);

    for (int cc = 0; cc < k; cc++) {
      cin >> a[c][cc];
    }
  }

  int i, j;
  for (int c = 0; c < q; c++) {
    cin >> i >> j;

    cout << a[i].at(j) << endl;
  }

  return 0;
}
