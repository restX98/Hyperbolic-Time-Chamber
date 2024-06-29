#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
  Node* next;
  Node* prev;
  int value;
  int key;
  Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
  Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
  map<int, Node*> mp; //map the key to the node in the linked list
  int cp;  //capacity
  Node* tail; // double linked list tail pointer
  Node* head; // double linked list head pointer
  virtual void set(int, int) = 0; //set function
  virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
public:
  LRUCache(int capacity) {
    cp = capacity;
    head = nullptr;
    tail = nullptr;
  }

  // Override set function
  void set(int key, int value) override {
    if (mp.find(key) != mp.end()) {
      Node* existingNode = mp[key];
      existingNode->value = value;
    } else {
      if (mp.size() == cp) {
        Node* nodeToRemove = head;
        remove(nodeToRemove);
        mp.erase(nodeToRemove->key);
        delete nodeToRemove;
      }
      Node* newNode = new Node(key, value);
      mp[key] = newNode;
      insert(newNode);
    }
  }

  // Override get function
  int get(int key) override {
    if (mp.find(key) != mp.end()) {
      Node* node = mp[key];
      return node->value;
    }
    return -1; // Return -1 if the key is not found
  }

  ~LRUCache() {
    Node* current = head;
    while (current != nullptr) {
      Node* next = current->next;
      delete current;
      current = next;
    }
  }

private:
  void remove(Node* node) {
    Node* prevNode = node->prev;
    Node* nextNode = node->next;
    if (prevNode != nullptr) {
      prevNode->next = nextNode;
    } else {
      head = nextNode;
    }
    if (nextNode != nullptr) {
      nextNode->prev = prevNode;
    } else {
      tail = prevNode;
    }
  }

  void insert(Node* node) {
    if (head == nullptr) {
      head = node;
    } else if (tail == nullptr) {
      tail = node;
      head->next = tail;
      tail->prev = head;
    } else {
      node->prev = tail;
      tail = node;
    }
  }
};

int main() {
  int n, capacity, i;
  cin >> n >> capacity;
  LRUCache l(capacity);
  for (i = 0;i < n;i++) {
    string command;
    cin >> command;
    if (command == "get") {
      int key;
      cin >> key;
      cout << l.get(key) << endl;
    } else if (command == "set") {
      int key, value;
      cin >> key >> value;
      l.set(key, value);
    }
  }
  return 0;
}
