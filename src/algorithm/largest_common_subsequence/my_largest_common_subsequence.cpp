#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main() {
  string scrollName = "QivcjGDoqoZKuiDcFHqRBdtuPRrisYZoSyQuERxvPiYZNfbWTZHqwLiCeebfYSAgSZiOc";
  string journal = "OAAeqEXEmijuQqDEDYBlklSWURxcLxHlFBYuWSWMYHWJVHXigdjohAundoufZ";

  vector<int> iIDs = vector<int>{};
  vector<int> jIDs = vector<int>{};

  int max = 0;

  int ii = 0;
  int jj = 0;
  int t_jj = jj;
  while (ii < scrollName.length()) {
    while (jj < journal.length()) {
      if (scrollName[ii] == journal[jj]) {
        iIDs.push_back(ii);
        jIDs.push_back(jj);
        t_jj = jj;
        jj++;
        break;
      }
      jj++;
    }
    jj = t_jj + 1;
    ii++;
  }
  max = iIDs.size();

  do {
    ii = iIDs.back();
    jj = jIDs.back() + 1;

    iIDs.pop_back();
    jIDs.pop_back();

    while (ii < scrollName.length()) {
      while (jj < journal.length()) {
        if (scrollName[ii] == journal[jj]) {
          iIDs.push_back(ii);
          jIDs.push_back(jj);
          jj++;
          break;
        }
        jj++;
      }
      jj = jIDs.back() + 1;
      ii++;
    }
    max = jIDs.size() > max ? jIDs.size() : max;
  } while (jIDs.size() > 0);

  iIDs.clear();
  jIDs.clear();

  string tmp = scrollName;
  scrollName = journal;
  journal = tmp;

  ii = 0;
  jj = 0;
  t_jj = jj;
  while (ii < scrollName.length()) {
    while (jj < journal.length()) {
      if (scrollName[ii] == journal[jj]) {
        iIDs.push_back(ii);
        jIDs.push_back(jj);
        t_jj = jj;
        jj++;
        break;
      }
      jj++;
    }
    jj = t_jj + 1;
    ii++;
  }
  max = jIDs.size() > max ? jIDs.size() : max;

  do {
    int t_jj = jIDs.back() + 1;

    ii = iIDs.back();
    jj = jIDs.back() + 1;

    iIDs.pop_back();
    jIDs.pop_back();

    while (ii < scrollName.length()) {
      while (jj < journal.length()) {
        if (scrollName[ii] == journal[jj]) {
          iIDs.push_back(ii);
          jIDs.push_back(jj);
          jj++;
          break;
        }
        jj++;
      }
      jj = jIDs.back() + 1;
      ii++;
    }
    max = jIDs.size() > max ? jIDs.size() : max;
  } while (jIDs.size() > 0);

  cout << max << endl;
  return 0;
}
