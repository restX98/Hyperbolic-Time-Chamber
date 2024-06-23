#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
protected:
  string name;
  int age;
public:
  virtual void getdata() {}
  virtual void putdata() {}
};

class Professor : public Person {
private:
  static inline int sequenceId{ 0 };
private:
  int publications;
  int cur_id;

public:
  static int getSequenceId() {
    return ++sequenceId;
  }
  Professor() {
    this->cur_id = Professor::getSequenceId();
  }
  virtual void getdata() {
    cin >> this->name;
    cin >> this->age;
    cin >> this->publications;
  }
  virtual void putdata() {
    cout << this->name << ' ' << this->age << ' ' << this->publications << ' ' << this->cur_id << endl;
  }
};

class Student : public Person {
private:
  static inline int sequenceId{ 0 };
private:
  int marks[6];
  int cur_id;
public:
  static int getSequenceId() {
    return ++sequenceId;
  }
  Student() {
    this->cur_id = Student::getSequenceId();
  }
  virtual void getdata() {
    cin >> this->name;
    cin >> this->age;
    cin >> this->marks[0] >> this->marks[1] >> this->marks[2] >> this->marks[3] >> this->marks[4] >> this->marks[5];
  }
  virtual void putdata() {
    cout << this->name << ' ' << this->age << ' ' << this->getMarksSum() << ' ' << this->cur_id << endl;
  }
  int getMarksSum() {
    int sum{ 0 };
    for (int mark : this->marks) {
      sum += mark;
    }
    return sum;
  }
};

int main() {

  int n, val;
  cin >> n; //The number of objects that is going to be created.
  Person* per[n];

  for (int i = 0;i < n;i++) {

    cin >> val;
    if (val == 1) {
        // If val is 1 current object is of type Professor
      per[i] = new Professor;

    } else per[i] = new Student; // Else the current object is of type Student

    per[i]->getdata(); // Get the data from the user.

  }

  for (int i = 0;i < n;i++)
    per[i]->putdata(); // Print the required output for each object.

  return 0;

}
