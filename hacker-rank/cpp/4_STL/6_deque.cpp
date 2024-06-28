#include <iostream>
#include <deque>
using namespace std;

void printKMax(int arr[], int n, int k) {
  int i;
  deque<int> d;

  int val{ 0 };
  for (i = 0; i < k; i++) {
    d.push_back(arr[i]);
  }
  int max = d[0];
  for (int j = 1; j < k; j++) {
    if (d[j] > max) max = d[j];
  }

  cout << max;

  for (int i = k; i < n; i++) {
    d.push_back(arr[i]);

    if (max == d.front()) {
      max = d[1];
      for (int j = 2; j < k + 1; j++) {
        if (d[j] > max) max = d[j];
      }
    } else if (d.back() > max) {
      max = d.back();
    }

    d.pop_front();

    cout << ' ' << max;
  }
  cout << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    int arr[n];
    for (int i = 0; i < n; i++) {
      cin >> arr[i];
    }
    printKMax(arr, n, k);
  }
  return 0;
}
