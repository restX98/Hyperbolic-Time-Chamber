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

  int q;
  cin >> q;

  int tq;
  for (int i = 0; i < q; i++) {
    cin >> tq;
    auto lower = lower_bound(v.begin(), v.end(), tq);

    string found;
    if (tq == *lower) {
      found = "Yes ";
    } else {
      found = "No ";
    }
    int id = distance(v.begin(), lower) + 1;

    cout << found << id << endl;
  }

  return 0;
}
