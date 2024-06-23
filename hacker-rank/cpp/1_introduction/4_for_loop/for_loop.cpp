#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;
int main() {

  vector<string> numbers{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

  int a, b;

  cin >> a >> b;

  for (int i = a; i <= b; i++) {
    if (i > 9) {
      if (i % 2 == 0) {
        cout << "even" << endl;
      } else {
        cout << "odd" << endl;
      }
    } else {
      cout << numbers[i - 1] << endl;
    }
  }

  return 0;
}
