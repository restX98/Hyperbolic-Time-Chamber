#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> split(string str, char delimiter);
string hrmlSelector(vector<string> hrml, string query);
string getAttribute(string str, string attribute);

/**
 * I know!
 * Tree Data Structure is the best way.
 * I'm just struggling with syntax and basics.
 */
int main() {

  int n, q;

  cin >> n >> q;

  vector<string> hrml;

  string line;
  for (int i = 0; i < n; i++) {
    std::getline(std::cin >> std::ws, line);
    hrml.push_back(line);
  }

  for (int i = 0; i < q; i++) {
    cin >> line;
    cout << hrmlSelector(hrml, line) << endl;
  }

  return 0;
}

vector<string> split(string str, char delimiter) {
  vector<string> tokens;
  string token;

  for (char c : str) {
    if (c == delimiter) {
      if (!token.empty()) {
        tokens.push_back(token);
        token.clear();
      }
    } else {
      token += c;
    }
  }

  if (!token.empty()) {
    tokens.push_back(token);
  }

  return tokens;
}

string getAttribute(string str, string attribute) {
  str = str.substr(0, str.size() - 1);

  vector<string> values = split(str, ' ');

  for (int i = 1; i < values.size(); i += 3) {
    if (attribute.compare(values[i]) == 0) {
      return values[i + 2].substr(1, values[i + 2].size() - 2);
    }
  }

  return "";
}


string hrmlSelector(vector<string> hrml, string query) {

  vector<string> queryPart = split(query, '~');

  vector<string> tags = split(queryPart[0], '.');
  string attribute = queryPart[1];

  string value = "";

  string tagToClose = "";

  int selectorId = 0;
  for (int i = 0; i < hrml.size(); i++) {
    if (!tagToClose.empty()) {
      if (hrml[i].compare(tagToClose) >= 0) {
        tagToClose = "";
      }
      continue;
    }

    if (hrml[i].find('<' + tags[selectorId]) != string::npos) {
      if (selectorId + 1 == tags.size()) {
        value = getAttribute(hrml[i], attribute);
        break;
      } else {
        selectorId++;
      }
    } else {
      tagToClose = "</" + split(hrml[i], ' ')[0].substr(1);
    }
  }

  return value.empty() ? "Not Found!" : value;
}
