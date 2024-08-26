#include <iostream>
#include <thread>

// Singleton class - Database
class Database {
private:
  static Database* mInstance;

protected: // We use protect to prevent the direct use but allow the derived use.

  Database(const std::string& dbName) : mName(dbName) {
    std::cout << "DB connection to " << dbName << "..." << std::endl;
    std::cout << "DB connected to " << dbName << "!" << std::endl;
  }

  std::string mName;

public:
  /**
   * Singletons should not be cloneable.
   */
  Database(Database& other) = delete;

  /**
   * Singletons should not be assignable.
   */
  void operator=(const Database&) = delete;

  static Database* getInstance(const std::string& value);

  // Business methods:
  void createRecord(const std::string& text) {
    std::cout << "New record created: " << text << std::endl;
  }

  std::string getName() const {
    return this->mName;
  }
};

Database* Database::mInstance = nullptr;

/**
 * Static methods should be defined outside the class (linkage problem).
 * Not a problem using headers.
 */
Database* Database::getInstance(const std::string& value) {
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
  if (mInstance == nullptr) {
    mInstance = new Database(value);
  }
  return mInstance;
}


void ThreadFoo() {
    // Following code emulates slow initialization.
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Database* db = Database::getInstance("FOO");
  std::cout << db->getName() << "\n";
}

void ThreadBar() {
    // Following code emulates slow initialization.
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Database* db = Database::getInstance("BAR");
  std::cout << db->getName() << "\n";
}


int main() {
  std::cout << "If you see the same value, then singleton was reused (yay!\n" <<
    "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
    "RESULT:\n";
  std::thread t1(ThreadFoo);
  std::thread t2(ThreadBar);
  t1.join();
  t2.join();

  return 0;
}
