#include<bits/stdc++.h>

using namespace std;

struct Workshop {
  int start_time;
  int duration;
  int end_time;
};

struct Available_Workshops {
  const int n;
  Workshop* workshops;
};

Available_Workshops* initialize(int* start_time, int* duration, int n) {
  Workshop* workshops = new Workshop[n];

  for (int i = 0; i < n; i++) {
    workshops[i] = Workshop{
        .start_time = start_time[i],
        .duration = duration[i],
        .end_time = start_time[i] + duration[i]
    };
  }

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (workshops[i].start_time > workshops[j].start_time) {
        Workshop tmp = workshops[i];
        workshops[i] = workshops[j];
        workshops[j] = tmp;
      }
    }
  }

  Available_Workshops* availableWorkshops = new Available_Workshops{
      .n = n,
      .workshops = workshops
  };

  return availableWorkshops;
}

int CalculateMaxWorkshops(Available_Workshops* availableWorkshops) {
  int n = availableWorkshops->n;
  int matrix[n][n];

  Workshop* workshops = availableWorkshops->workshops;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }

  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j++) {
      Workshop w_i = workshops[i - 1];
      Workshop w_j = workshops[j];

      if (w_i.end_time <= w_j.start_time) {
        int val = matrix[i - 1][i - 1] + 1;
        while (j < n) {
          matrix[i][j++] = val;
        }
      } else {
        matrix[i][j] = matrix[i - 1][j];
      }
    }
  }

  return matrix[n - 1][n - 1] + 1;
}

int main(int argc, char* argv[]) {
  int n; // number of workshops
  cin >> n;
  // create arrays of unknown size n
  int* start_time = new int[n];
  int* duration = new int[n];

  for (int i = 0; i < n; i++) {
    cin >> start_time[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> duration[i];
  }

  Available_Workshops* ptr;
  ptr = initialize(start_time, duration, n);
  cout << CalculateMaxWorkshops(ptr) << endl;
  return 0;
}
