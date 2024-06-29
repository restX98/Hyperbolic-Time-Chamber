#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {

  vector<int> nums;

  int n;
  cin >> n;

  int t;
  for (int i = 0; i < n; i++) {
    cin >> t;
    nums.push_back(t);
  }

  sort(nums.begin(), nums.end());

  for (int i : nums) {
    cout << i << ' ';
  }
  cout << endl;

  return 0;
}
