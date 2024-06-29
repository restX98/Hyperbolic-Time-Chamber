#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

vector<int> parseInts(string str);

int main() {

  string str;

  cin >> str;

  vector<int> numbers = parseInts(str);

  for (int n : numbers) {
    cout << n << endl;
  }

  return 0;
}

vector<int> parseInts(string str) {
  stringstream ss;
  ss << str;

  vector<int> ints;
  int n;
  char c;

  while (ss >> n >> c) {
    ints.push_back(n);
  }
  ints.push_back(n);

  return ints;
}
