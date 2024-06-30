#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
  int n;
  cin >> n;

  // Define the flags for each stream a single time.
  ostringstream aSS, bSS, cSS;
  aSS << showbase << hex;
  bSS << right << fixed << showpos << setw(15) << setfill('_') << setprecision(2);
  cSS << uppercase << scientific << setprecision(9);
  ios aFmt(NULL), bFmt(NULL), cFmt(NULL);
  aFmt.copyfmt(aSS);
  bFmt.copyfmt(bSS);
  cFmt.copyfmt(cSS);

  int filler;
  double a, b, c;
  string bStr, cStr;
  while (n--) {
    cin >> a >> b >> c;
    aSS << (long long)a;
    bSS << b;
    cSS << c;

    // Print all and reset for the next iteration
    cout << aSS.str() << std::endl;
    cout << bSS.str() << std::endl;
    cout << cSS.str() << std::endl;
    aSS.str("");
    bSS.str("");
    cSS.str("");
    aSS.copyfmt(aFmt);
    bSS.copyfmt(bFmt);
    cSS.copyfmt(cFmt);
  }
}
