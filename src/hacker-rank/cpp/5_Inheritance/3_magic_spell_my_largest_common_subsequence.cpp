#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell {
private:
  string scrollName;
public:
  Spell() : scrollName("") {}
  Spell(string name) : scrollName(name) {}
  virtual ~Spell() {}
  string revealScrollName() {
    return scrollName;
  }
};

class Fireball : public Spell {
private: int power;
public:
  Fireball(int power) : power(power) {}
  void revealFirepower() {
    cout << "Fireball: " << power << endl;
  }
};

class Frostbite : public Spell {
private: int power;
public:
  Frostbite(int power) : power(power) {}
  void revealFrostpower() {
    cout << "Frostbite: " << power << endl;
  }
};

class Thunderstorm : public Spell {
private: int power;
public:
  Thunderstorm(int power) : power(power) {}
  void revealThunderpower() {
    cout << "Thunderstorm: " << power << endl;
  }
};

class Waterbolt : public Spell {
private: int power;
public:
  Waterbolt(int power) : power(power) {}
  void revealWaterpower() {
    cout << "Waterbolt: " << power << endl;
  }
};

class SpellJournal {
public:
  static string journal;
  static string read() {
    return journal;
  }
};
string SpellJournal::journal = "";

void counterspell(Spell* spell) {

  Fireball* fireball = dynamic_cast<Fireball*>(spell);
  if (fireball != nullptr) {
    fireball->revealFirepower();
    return;
  }

  Frostbite* frostbite = dynamic_cast<Frostbite*>(spell);
  if (frostbite != nullptr) {
    frostbite->revealFrostpower();
    return;
  }
  Thunderstorm* thunderstorm = dynamic_cast<Thunderstorm*>(spell);
  if (thunderstorm != nullptr) {
    thunderstorm->revealThunderpower();
    return;
  }
  Waterbolt* waterbolt = dynamic_cast<Waterbolt*>(spell);
  if (waterbolt != nullptr) {
    waterbolt->revealWaterpower();
    return;
  }

  string scrollName = spell->revealScrollName();
  string journal = SpellJournal::journal;

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
}

class Wizard {
public:
  Spell* cast() {
    Spell* spell;
    string s; cin >> s;
    int power; cin >> power;
    if (s == "fire") {
      spell = new Fireball(power);
    } else if (s == "frost") {
      spell = new Frostbite(power);
    } else if (s == "water") {
      spell = new Waterbolt(power);
    } else if (s == "thunder") {
      spell = new Thunderstorm(power);
    } else {
      spell = new Spell(s);
      cin >> SpellJournal::journal;
    }
    return spell;
  }
};

int main() {
  int T;
  cin >> T;
  Wizard Arawn;
  while (T--) {
    Spell* spell = Arawn.cast();
    counterspell(spell);
  }
  return 0;
}
