#include <iostream>
#include <math.h>
using namespace std;

/**
 * Example:
 * 1010 = 10
 *
 * val = 1;           1010[0]
 * val = 0 + 2*1 = 2  1010[1]
 * val = 1 + 2*2 = 5  1010[2]
 * val = 0 + 2*5 = 10 1010[3]
 */

int recursive_binaries(bool head) {
  int val = static_cast<int>(head);
  return val;
}

template<typename ... Args>
int recursive_binaries(bool head, Args ... args) {
  int val = static_cast<int>(head) + 2 * recursive_binaries(args...);
  return val;
}

template<bool ...digits>
int reversed_binary_value() {
  return recursive_binaries(digits...);
};

template <int n, bool...digits>
struct CheckValues {
  static void check(int x, int y) {
    CheckValues<n - 1, 0, digits...>::check(x, y);
    CheckValues<n - 1, 1, digits...>::check(x, y);
  }
};

template <bool...digits>
struct CheckValues<0, digits...> {
  static void check(int x, int y) {
    int z = reversed_binary_value<digits...>();
    cout << z << endl;
    std::cout << (z + 64 * y == x);
  }
};

int main() {
  int t; std::cin >> t;

  for (int i = 0; i != t; ++i) {
    int x, y;
    cin >> x >> y;
    CheckValues<6>::check(x, y);
    cout << "\n";
  }
}
