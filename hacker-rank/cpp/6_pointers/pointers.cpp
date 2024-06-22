#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void update(int* a, int* b);

int main() {
  int a, b;

  cin >> a;
  cin >> b;

  update(&a, &b);

  cout << a << endl;
  cout << b << endl;

  return 0;
}


void update(int* a, int* b) {
  int aa = (*a) + (*b);
  int bb = ((*a) - (*b));

  if (bb < 0) {
    bb = bb * -1;
  }

  *a = aa;
  *b = bb;
}
