#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


int main() {

  int q;
  cin >> q;

  set<int> s;
  int x, y;
  while (q--) {
    cin >> y >> x;
    if (y == 1) {
      s.insert(x);
    } else if (y == 2) {
      s.erase(x);
    } else if (y == 3) {
      if (s.find(x) != s.end()) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    }
  }

  return 0;
}
