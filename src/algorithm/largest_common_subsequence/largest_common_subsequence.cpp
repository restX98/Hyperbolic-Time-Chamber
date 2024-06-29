#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {

  string scrollName = "QivcjGDoqoZKuiDcFHqRBdtuPRrisYZoSyQuERxvPiYZNfbWTZHqwLiCeebfYSAgSZiOc";
  string journal = "OAAeqEXEmijuQqDEDYBlklSWURxcLxHlFBYuWSWMYHWJVHXigdjohAundoufZ";

  int matrix[scrollName.length() + 1][journal.length() + 1];
  for (int i = 0; i <= scrollName.length(); i++) {
    for (int j = 0; j <= journal.length(); j++) {
      matrix[i][j] = 0;
    }
  }

  for (int i = scrollName.length() - 1; i >= 0; i--) {
    for (int j = journal.length() - 1; j >= 0; j--) {
      if (scrollName[i] == journal[j]) {
        matrix[i][j] = matrix[i + 1][j + 1] + 1;
      } else {
        matrix[i][j] = matrix[i + 1][j] > matrix[i][j + 1] ? matrix[i + 1][j] : matrix[i][j + 1];
      }
    }
  }
  cout << matrix[0][0] << endl;

  return 0;
}
