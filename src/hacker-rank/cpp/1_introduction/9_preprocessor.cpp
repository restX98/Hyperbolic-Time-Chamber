#include <limits>

#define FUNCTION(func, op) void func(int& a, int& b) { a = (a op b) ? a : b; }
#define foreach(v, i) for(int i = 0; i< static_cast<int>(v.size()); i++)
#define io(v) cin >> v
#define toStr(val) #val /*stringify operator-> # */
#define INF numeric_limits<int>::max()

#include <iostream>
#include <vector>
using namespace std;

#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif 

FUNCTION(minimum, < )
FUNCTION(maximum, > )

int main() {
  int n; cin >> n;
  vector<int> v(n);
  foreach(v, i) {
    io(v)[i];
  }
  int mn = INF;
  int mx = -INF;
  foreach(v, i) {
    minimum(mn, v[i]);
    maximum(mx, v[i]);
  }
  int ans = mx - mn;
  cout << toStr(Result = ) << ' ' << ans;
  return 0;
}
