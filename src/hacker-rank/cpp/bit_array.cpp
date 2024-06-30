#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int main() {
  int n, s, p, q;

  cin >> n >> s >> p >> q;

  int pow_2_31 = static_cast<int>(pow(2, 31));

  int tortoise = s % n;
  int hare = (tortoise * p + q) % n;

  int c = 1;
  while (tortoise != hare) {
    if (c == n) break;

    int tmp = hare;
    hare = (hare * p + q) % pow_2_31;
    tortoise = tmp;
    c++;
  }
  if (tortoise == hare) c--;

  cout << c << endl;

  return 0;
}
