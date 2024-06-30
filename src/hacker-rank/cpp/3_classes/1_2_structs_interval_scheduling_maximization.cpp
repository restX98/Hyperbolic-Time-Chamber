#include<bits/stdc++.h>

using namespace std;

struct Workshop {
  int start_time, duration, end_time;

  Workshop() {}

  Workshop(int start_time, int duration, int end_time) : start_time(start_time), duration(duration), end_time(end_time) {}
};

struct Available_Workshops {
  int n;
  vector<Workshop> workshops;

  Available_Workshops(int n) : n(n) {
    workshops.reserve(n);
  }
};

Available_Workshops* initialize(int start_time[], int duration[], int n) {
  Available_Workshops* avbl_workshop = new Available_Workshops(n);

  for (int i = 0; i < n; i++) {
    avbl_workshop->workshops.push_back(Workshop(start_time[i], duration[i], start_time[i] + duration[i]));
  }

  delete[] start_time;
  delete[] duration;

  return avbl_workshop;
}

bool end_time_sorter(const Workshop& workshop_1, const Workshop& workshop_2) {
  return workshop_1.end_time > workshop_2.end_time;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
  sort(ptr->workshops.begin(), ptr->workshops.end(), end_time_sorter);
  int curr_end_time, workshop_count = 0;

  while (static_cast<int>((ptr->workshops).size()) > 0) {
    curr_end_time = ptr->workshops.back().end_time;

    for (int i = static_cast<int>(ptr->workshops.size()) - 1; i >= 0; i--) {
      if (ptr->workshops[i].start_time < curr_end_time) {
        ptr->workshops.erase(ptr->workshops.begin() + i);
      }
    }

    workshop_count += 1;
  }

  delete ptr;
  return workshop_count;
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
