#include <iostream>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;

template<>
class Traits<Color> {
public:
  static string name(int id) {
    if (static_cast<int>(Color::red) == id) {
      return "red";
    } else if (static_cast<int>(Color::green) == id) {
      return "green";
    } else if (static_cast<int>(Color::orange) == id) {
      return "orange";
    } else {
      return "unknown";
    }
  }
};

template<>
class Traits<Fruit> {
public:
  static string name(int id) {
    if (static_cast<int>(Fruit::apple) == id) {
      return "apple";
    } else if (static_cast<int>(Fruit::orange) == id) {
      return "orange";
    } else if (static_cast<int>(Fruit::pear) == id) {
      return "pear";
    } else {
      return "unknown";
    }
  }
};

int main() {
  int t = 0; std::cin >> t;

  for (int i = 0; i != t; ++i) {
    int index1; std::cin >> index1;
    int index2; std::cin >> index2;
    cout << Traits<Color>::name(index1) << " ";
    cout << Traits<Fruit>::name(index2) << "\n";
  }
}
