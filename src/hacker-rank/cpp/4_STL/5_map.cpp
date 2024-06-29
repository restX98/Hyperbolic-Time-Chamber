#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;


int main() {

  int q;
  cin >> q;

  map<string, int> m;

  string x;
  int type, y;
  while (q--) {
    cin >> type;
    if (type == 1) {
      cin >> x >> y;
      if (m.find(x) != m.end()) {
        m[x] += y;
      } else {
        m.insert(make_pair(x, y));
      }
    } else if (type == 2) {
      cin >> x;
      m.erase(x);
    } else if (type == 3) {
      cin >> x;
      if (m.find(x) != m.end()) {
        cout << m[x] << endl;
      } else {
        cout << "0" << endl;
      }
    }
  }

  return 0;
}
