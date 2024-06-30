#include<bits/stdc++.h>

// Input:
// 13
// 58 32 100 15 31 48 90 81 74 23 2 15 62
// 4 10 7 2 4 2 4 8 10 3 10 2 1

struct Activity {
  int start_time;
  int end_time;
  int duration;
};

bool activity_sorter(const Activity& left, const Activity& right) {
  return left.end_time > right.end_time;
}

int main(int argc, char* argv[]) {
  int n; // number of workshops
  std::cin >> n;
  // create arrays of unknown size n
  int* start_time = new int[n];
  int* duration = new int[n];

  for (int i = 0; i < n; i++) {
    std::cin >> start_time[i];
  }
  for (int i = 0; i < n; i++) {
    std::cin >> duration[i];
  }

  std::vector<Activity> activities;
  for (int i = 0; i < n; i++) {
    activities.push_back(Activity{
      .start_time = start_time[i],
      .end_time = start_time[i] + duration[i],
      .duration = duration[i]
      }
    );
  }
  std::sort(activities.begin(), activities.end(), activity_sorter);

  int lastEndTime = activities.begin()->end_time;
  int count = 1;
  for (int i = 0; i < static_cast<int>(activities.size()); i++) {
    if (lastEndTime <= activities[i].start_time) {
      lastEndTime = activities[i].end_time;
      count++;
    }
  }

  std::cout << count;

  return 0;
}
