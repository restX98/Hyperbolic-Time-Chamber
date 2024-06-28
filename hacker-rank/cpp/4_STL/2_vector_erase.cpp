#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {

  int n;
  cin >> n;

  vector<int> v;

  int t;
  for (int i = 0; i < n; i++) {
    cin >> t;
    v.push_back(t);
  }

  int x;
  cin >> x;

  v.erase(v.begin() + x - 1);

  int a, b;
  cin >> a >> b;

  v.erase(v.begin() + a - 1, v.begin() + b - 1);

  cout << v.size() << endl;
  for (int i : v) {
    cout << i << ' ';
  }
  cout << endl;

  return 0;
}
