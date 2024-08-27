#include <map>
#include <iostream>
#include <cassert>

template<typename K, typename V>
class interval_map {
  friend void IntervalMapTest();
  V m_valBegin;
  std::map<K, V> m_map;
public:
  // constructor associates whole range of K with val
  interval_map(V const& val)
    : m_valBegin(val) {
  }

 // Assign value val to interval [keyBegin, keyEnd).
 // Overwrite previous values in this interval.
 // Conforming to the C++ Standard Library conventions, the interval
 // includes keyBegin, but excludes keyEnd.
 // If !( keyBegin < keyEnd ), this designates an empty interval,
 // and assign must do nothing.

  void assign(K const& keyBegin, K const& keyEnd, V const& val) {
    if (!(keyBegin < keyEnd)) return; // Empty Interval

    auto itBegin = m_map.lower_bound(keyBegin); // Get map element with key equal or greater than keyBegin
    auto itEnd = m_map.lower_bound(keyEnd); // Get map element with key equal or greater than keyEnd

    V prevEndVal = (itEnd != m_map.begin()) ? std::prev(itEnd)->second : m_valBegin;

    if (itBegin != m_map.begin()) { // If true means that the keyBegin is not the lower existing
      auto prev = std::prev(itBegin); // Take the previous key on the map
      if (prev->second == val) { // If true means that the sequence is already started in a lower key
        itBegin = prev; // Assign prev to itBegin to use it as lower bound of the sequence
      } else if (itBegin != m_map.end() && itBegin->first == keyBegin) { // If true means that the key already exists, then we can just override the value
        itBegin->second = val;
      } else { // Else we need to create the key and assign the value
        itBegin = m_map.insert_or_assign(itBegin, keyBegin, val);
      }
    } else { // If false means that the begin key is the lower of the existing one, then we can freely valorize the key map 
      if (m_valBegin != val) { // If try to add at the begin of the sequence the valBegin, then skip it
        itBegin = m_map.insert_or_assign(itBegin, keyBegin, val);
      }
    }

    // Set the end of sequence only if itEnd is the end of the map
    // or if the ifEnd key doesn't exists already
    if (itEnd == m_map.end() || itEnd->first != keyEnd) {
      if (prevEndVal != val) {
        m_map.insert_or_assign(itEnd, keyEnd, prevEndVal);
      }
    }

    // Erase the elements in the range (keyBegin, keyEnd) that now have the same value as val
    if (!m_map.empty() && itBegin != m_map.end() && itEnd != m_map.begin() && std::next(itBegin) != itEnd) {
      m_map.erase(std::next(itBegin), std::prev(itEnd));
    }
  }

  // look-up of the value associated with key
  V const& operator[](K const& key) const {
    auto it = m_map.upper_bound(key);
    if (it == m_map.begin()) {
      return m_valBegin;
    } else {
      return (--it)->second;
    }
  }
};

void IntervalMapTest() {
  interval_map<int, char> map('A');
  map.assign(5, 5, 'B');
  assert(map[4] == 'A');
  assert(map[5] == 'A');
  assert(map[6] == 'A');

  interval_map<int, char> map1('A');
  map1.assign(3, 8, 'A');
  map1.assign(9, 12, 'A');
  assert(map1[2] == 'A');
  assert(map1[3] == 'A');
  assert(map1[7] == 'A');
  assert(map1[8] == 'A');
  assert(map1.m_map.empty());

  interval_map<int, char> map2('A');
  map2.assign(3, 5, 'B');
  assert(map2[2] == 'A');
  assert(map2[3] == 'B');
  assert(map2[4] == 'B');
  assert(map2[5] == 'A');
  assert(map2[6] == 'A');

  interval_map<int, char> map3('A');
  map3.assign(3, 5, 'B');
  map3.assign(5, 7, 'B');
  assert(map3[2] == 'A');
  assert(map3[3] == 'B');
  assert(map3[6] == 'B');
  assert(map3[7] == 'A');

  interval_map<int, char> map4('A');
  map4.assign(3, 7, 'B');
  map4.assign(5, 9, 'C');
  assert(map4[4] == 'B');
  assert(map4[5] == 'C');
  assert(map4[8] == 'C');
  assert(map4[9] == 'A');

  interval_map<int, char> map5('A');
  map5.assign(3, 7, 'B');
  map5.assign(5, 6, 'B');
  assert(map5[2] == 'A');
  assert(map5[3] == 'B');
  assert(map5[5] == 'B');
  assert(map5[6] == 'B');
  assert(map5[7] == 'A');

  interval_map<int, char> map6('A');
  map6.assign(3, 5, 'B');
  map6.assign(7, 9, 'C');
  map6.assign(4, 8, 'D');
  assert(map6[3] == 'B');
  assert(map6[4] == 'D');
  assert(map6[7] == 'D');
  assert(map6[8] == 'C');
  assert(map6[9] == 'A');

  interval_map<int, char> map7('A');
  map7.assign(3, 6, 'B');
  map7.assign(6, 8, 'B');
  assert(map7[2] == 'A');
  assert(map7[3] == 'B');
  assert(map7[7] == 'B');
  assert(map7[8] == 'A');
  assert(map7.m_map.size() == 2);

  interval_map<int, char> map8('A');
  map8.assign(3, 6, 'B');
  map8.assign(4, 5, 'A');
  assert(map8[2] == 'A');
  assert(map8[3] == 'B');
  assert(map8[4] == 'A');
  assert(map8[5] == 'B');
  assert(map8[6] == 'A');

  interval_map<int, char> map9('A');
  map9.assign(0, 100, 'B');
  map9.assign(50, 150, 'C');
  map9.assign(10, 60, 'D');
  assert(map9[-1] == 'A');
  assert(map9[0] == 'B');

  interval_map<int, char> map10('A');
  map10.assign(2, 5, 'B');  // Initially creates an interval [2, 5) with 'B'
  map10.assign(3, 5, 'B');  // Overwriting [3, 5) with 'B'

  assert(map10[2] == 'B');
  assert(map10[3] == 'B');
  assert(map10[4] == 'B');
  assert(map10[5] == 'A');  // Key 5 should still map to 'A'
  assert(map10.m_map.size() == 2);  // Only one entry at key 2

  interval_map<int, char> map11('A');
  map11.assign(2, 6, 'B');  // Creates interval [2, 6) with 'B'
  map11.assign(4, 6, 'B');  // Extends or overlaps with [4, 6) with 'B'

  assert(map11[3] == 'B');
  assert(map11[4] == 'B');
  assert(map11[5] == 'B');
  assert(map11[6] == 'A');  // Key 6 should still map to 'A'
  assert(map11.m_map.size() == 2);  // Only one entry at key 2

  interval_map<int, char> map12('A');
  map12.assign(1, 4, 'C');  // Creates interval [1, 4) with 'C'
  map12.assign(3, 6, 'C');  // Extends the interval [3, 6) with 'C'

  assert(map12[2] == 'C');
  assert(map12[3] == 'C');
  assert(map12[4] == 'C');
  assert(map12[5] == 'C');
  assert(map12[6] == 'A');  // Key 6 should still map to 'A'
  assert(map12.m_map.size() == 2);  // Only one entry at key 1
}

int main() {
  IntervalMapTest();
  return 0;
}
